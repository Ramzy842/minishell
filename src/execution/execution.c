/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/19 14:49:45 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *get_cmd_abs_path(t_env *env, char *cmd)
{
    t_env *path = get_env(env, "PATH");
    if (!path)
        return NULL;
    char **path_spl = ft_split(path->value, ':');
    if (!path_spl)
        return NULL;
    int i = 0;
    while (path_spl[i])
    {
        char *tmp1 = ft_strjoin(path_spl[i], "/");
        char *tmp2 = ft_strjoin(tmp1, cmd);
        free(tmp1);
        if (!access(tmp2, F_OK))
            return tmp2;
        i++;
    }
    return (NULL);
}

int exec_builtin_commands(t_commands *cmd, t_env *env)
{

    if (strcmp(cmd->command_args[0], "cd") == 0)
        buit_cd(cmd); // done
    if (strcmp(cmd->command_args[0], "pwd") == 0)
        ft_pwd(); // done
    if (strcmp(cmd->command_args[0], "echo") == 0)
        bult_echo(cmd); // done
    if (strcmp(cmd->command_args[0], "export") == 0)
        bult_export(cmd, env); // still
    
       if (strcmp(cmd->command_args[0], "unset") == 0)
       bult_unset( cmd ,env); 
    if (strcmp(cmd->command_args[0], "env") == 0)
        bult_env(env); // still
    if (strcmp(cmd->command_args[0], "exit") == 0)
       bult_exit(cmd->command_args); // done
       
    return (0);
}
int check_and_handle_command(t_commands *cmd, t_env *env)
{

    char *cmd_abs_path = get_cmd_abs_path(env, cmd->command_args[0]);
    // command absolute path khasso ikhdm done
    if (cmd->command_args[0] && !cmd_abs_path && !check_is_builting(cmd))
    {
        printf("msh: %s: command not found\n", cmd->command_args[0]);
        cmd = cmd->next;
        return 0;
    }
    if (access(cmd_abs_path, X_OK) < 0 && cmd->command_args[0] && !check_is_builting(cmd))
    {
        printf("msh: %s: permission denied\n", cmd->command_args[0]);
        cmd = cmd->next;
        return 0;
    }

    return 1;
}

int check_is_builting(t_commands *cmd)
{
    if (strcmp(cmd->command_args[0], "cd") == 0)
    {
        return (1);
    }
    if (strcmp(cmd->command_args[0], "pwd") == 0)
    {
        return (1);
    }
    if (strcmp(cmd->command_args[0], "echo") == 0)
    {
        return (1);
    }
    if (strcmp(cmd->command_args[0], "env") == 0)
    {
        return (1);
    }
    if (strcmp(cmd->command_args[0], "export") == 0)
    {
        return (1);
    }
    if (strcmp(cmd->command_args[0], "unset") == 0)
    {
        return (1);
    }
    if (strcmp(cmd->command_args[0], "exit") == 0)
    {
        return (1);
    }
    return (0);
}

int minishell_execute(t_commands *cmd, t_env *env, t_data *data)
{
    (void)*data;
    int original_fd[2];
    int tmp_fd = -1;

    check_and_handle_command(cmd, env);
    // if (!cmd || !cmd->command_args || !cmd->command_args[0])
    // {
    //     // printf("empty commands \n");
    //     return 0;
    // }
    if (!cmd->command_args || !cmd->command_args[0])
    {
        // printf("empty commands \n");
        return 0;
    }

    original_fd[0] = dup(0);
    original_fd[1] = dup(1);

    if (!cmd->next && !ft_redir(cmd))
    {
        if (check_is_builting(cmd))
        {
            exec_builtin_commands(cmd, env);
        }
        else
        {
            // Fork for external commands
            int pid = fork();

            if (pid == 0)
            {
                execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
                // If execve fails, exit with an error code
                // exit(1);
            }
            else if (pid < 0)
            {
                // Handle fork error
                perror("fork");
                exit(1);
            }

            // Wait for the child process to complete
            int status;
            waitpid(pid, &status, 0);
        }

        dup2(original_fd[0], 0);
        dup2(original_fd[1], 1);
    }

    if (cmd->next)
    {
        int i = 0;
        int pid;

        while (cmd)
        {
            int pipefd[2];
            pipe(pipefd);
            pid = fork();

            if (pid == 0)
            {
                if (i == 0)
                {
                    dup2(pipefd[1], 1);
                }
                else if (i > 0 && cmd->next)
                {
                    dup2(tmp_fd, 0);
                    dup2(pipefd[1], 1);
                }
                else if (!cmd->next)
                {
                    dup2(tmp_fd, 0);
                }

                ft_redir(cmd);
                close(pipefd[0]);
                close(pipefd[1]);

                if (check_is_builting(cmd))
                {
                    exec_builtin_commands(cmd, env);
                }
                else
                {
                    // Fork for external commands
                    execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
                    // If execve fails, exit with an error code
                    exit(1);
                }

                // Exiting the child process is important here.
                exit(1);
            }
            else if (pid > 0)
            {
                if (tmp_fd > 2)
                {
                    close(tmp_fd);
                }

                if (cmd->next)
                {
                    tmp_fd = pipefd[0];
                }

                close(pipefd[1]);
            }

            i++;
            cmd = cmd->next;
        }
    }

    // Restore original file descriptors after execution
    dup2(original_fd[0], 0);
    dup2(original_fd[1], 1);

    // Wait for all child processes to finish
    while (wait(NULL) > 0)
        ;

    return 0;
}

// int minishell_execute(t_commands *cmd, t_env *env, t_data *data)
// {
// 	(void)*data;
//     int original_fd[2];
//     int tmp_fd = -1;

// 	check_and_handle_command(cmd, env);
//     if (!cmd || !cmd->command_args || !cmd->command_args[0])
//     {
//         // printf("empty commands \n");
//         exit(0);
//     }

//     original_fd[0] = dup(0);
//     original_fd[1] = dup(1);

//     if (!cmd->next && !ft_redir(cmd))
//     {
//         if (check_is_builting(cmd))
//         {
//             exec_builtin_commands(cmd);
//         }
//         else
//         {
//             execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
//         }

//         dup2(original_fd[0], 0);
//         dup2(original_fd[1], 1);
// 		 /// fork here for child procc
//     }

//     if (cmd->next)
//     {
//         int i = 0;
//         int pid;

//         while (cmd)
//         {
//             int pipefd[2];
//             pipe(pipefd);
//             pid = fork();

//             if (pid == 0)
//             {
//                 if (i == 0)
//                 {
//                     dup2(pipefd[1], 1);
//                 }
//                 else if (i > 0 && cmd->next)
//                 {
//                     dup2(tmp_fd, 0);
//                     dup2(pipefd[1], 1);
//                 }
//                 else if (!cmd->next)
//                 {
//                     dup2(tmp_fd, 0);
//                 }

//                 ft_redir(cmd);
//                 close(pipefd[0]);
//                 close(pipefd[1]);

//                 if (check_is_builting(cmd))
//                 {
//                     exec_builtin_commands(cmd);
//                 }
//                 else
//                 {
//                     execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
//                 }

//                 // Exiting the child process is important here.
//                  exit(1);
//             }
//             else if (pid > 0)
//             {
//                 if (tmp_fd > 2)
//                 {
//                     close(tmp_fd);
//                 }

//                 if (cmd->next)
//                 {
//                     tmp_fd = pipefd[0];
//                 }

//                 close(pipefd[1]);
//             }

//             i++;
//             cmd = cmd->next;
//         }
//     }

//     // Restore original file descriptors after execution
//     dup2(original_fd[0], 0);
//     dup2(original_fd[1], 1);

//     // Wait for all child processes to finish
//     while (wait(NULL) > 0);
//     return 0;
// }

// int minishell_execute(t_commands *cmd, t_env *env, t_data *data)
// {
// 	(void)*data;
// 	int pid;
// 	int tmp_fd =-1;
// 	int pipefd[2];
// 	int original_fd[2];
// 	int	i = 0;
// 	// t_commands *tmp;
// 	if (!cmd || !cmd->command_args || !cmd->command_args[0]) // no args
// 	{
// 		printf("empty commands \n");
// 		exit(0);
// 	}
// 	original_fd[0] = dup(0);
// 	original_fd[1] = dup(1);
// 	if ( !cmd->next  && !ft_redir(cmd))
// 	{
// 		if(check_is_builting(cmd))
// 		{
// 			exec_builtin_commands(cmd);
// 			dup2(original_fd[0], 0);
// 			dup2(original_fd[1], 1);
// 			return(0);
// 		}
// 		else
// 			//  pid  =  fork();
// 			execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
// 			//  elseif (pid > 0)
// 			//  original_fd dup2() //Minishell-> echo yes > fileB case
// 	}
// 	if(cmd->next)
// 	{
// 		while(cmd)
// 		{
// 			pipe(pipefd);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (i == 0)
// 					dup2(pipefd[1], 1);
// 				else if (i > 0 && cmd->next) {
// 					dup2(tmp_fd, 0);
// 					dup2(pipefd[1], 1);
// 				}
// 				else if (!cmd->next)
// 					dup2(tmp_fd, 0);
// 				ft_redir(cmd);
// 				close(pipefd[0]);
// 				close(pipefd[0]);
// 				if (check_is_builting(cmd)) {
// 					exec_builtin_commands(cmd);
// 				} else {
// 					execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
// 				}
// 			}
// 			else if (pid > 0) {
// 				if (tmp_fd > 2)
// 					close(tmp_fd);
// 				if (cmd->next)
// 					tmp_fd = pipefd[0];
// 				close(pipefd[1]);
// 			}

// 		i++;
// 		cmd = cmd->next;
// 		}
// 		waitpid(pid, NULL, 0);
// 	}
// 	return 0;
// }
