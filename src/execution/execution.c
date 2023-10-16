/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 06:44:55 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



char* get_cmd_abs_path(t_env* env, char* cmd)
{
	t_env* path = get_env(env, "PATH");
	if (!path)
		return NULL;
	char** path_spl = ft_split(path->value, ':');
	if (!path_spl)
		return NULL;
	int i = 0;
	while (path_spl[i])
	{
		char* tmp1 = ft_strjoin(path_spl[i], "/");
		char* tmp2 = ft_strjoin(tmp1, cmd);
		free(tmp1);
		if (!access(tmp2, F_OK))
			return tmp2;
		i++;
	}
	return (NULL);
}

int check_if_builting(t_commands *cmd)
{
	if (strcmp(cmd->command_args[0], "cd") == 0) {
		return (1);
    } else if (strcmp(cmd->command_args[0], "pwd") == 0) {
		return (1);
    } else if (strcmp(cmd->command_args[0], "echo") == 0) {
		return (1);
    } else if (strcmp(cmd->command_args[0], "export") == 0) {
		return (1);
    } else if (strcmp(cmd->command_args[0], "unset") == 0) {  
		return (1);
    } else if (strcmp(cmd->command_args[0], "exit") == 0) { 
		return (1);
	}
	return (0);
}

int handle_builtin_commands(t_data *data, t_commands *cmd) {
    if (strcmp(cmd->command_args[0], "cd") == 0) {
	
        buit_cd(data, cmd);
    } else if (strcmp(cmd->command_args[0], "pwd") == 0) {
		
        ft_pwd();
    } else if (strcmp(cmd->command_args[0], "echo") == 0) {
        bult_echo(data, cmd); // done
    } else if (strcmp(cmd->command_args[0], "export") == 0) {
		bult_export(data, cmd);
    } else if (strcmp(cmd->command_args[0], "unset") == 0) {
		bult_unset(data, cmd);
	} else if (strcmp(cmd->command_args[0], "exit") == 0) {
		bult_exit(data, cmd);//done
	}
	return (0);
}
int check_and_handle_command(t_commands* cmd, t_env* env) {



    char* cmd_abs_path = get_cmd_abs_path(env, cmd->command_args[0]);

    if (!cmd_abs_path && cmd->command_args[0]) {
        printf("msh: %s: command not found\n", cmd->command_args[0]);
        cmd = cmd->next;
        return 0;
    }

    if (access(cmd_abs_path, X_OK) < 0 && cmd->command_args[0]) {
        printf("msh: %s: permission denied\n", cmd->command_args[0]);
        cmd = cmd->next;
		return 0;
    }

    return 1;
}

int minishell_execute(t_commands* cmd, t_env* env , t_data *data)
{
	(void)*data;
	int pid;
	int tmp_fd = 0;
	int pipefd[2];
	t_commands *tmp;
	if (!cmd || !cmd->command_args || !cmd->command_args[0])
		return(0);
	// if ( check_if_builting(cmd))
	// 	return (handle_builtin_commands(data, cmd));
	
	tmp = cmd;
	while (cmd)
	{
		
		pipe(pipefd);
		pid = fork();
		if (!pid)
		{
			close (pipefd[0]);
			if (tmp_fd)
			{
				dup2(tmp_fd,STDIN_FILENO);
				close(tmp_fd);
			}
			if (cmd->next)
				dup2(pipefd[1], STDOUT_FILENO);
			close (pipefd[1]);
			ft_redir(cmd);
			
			execve(get_cmd_abs_path(env, cmd->command_args[0]), cmd->command_args, convert_env_to_arr(env));
			exit(EXIT_FAILURE);
		}
		else
		{
			close( pipefd[1]);
			if (tmp_fd)
				close(tmp_fd);
			tmp_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	while (tmp)
	{
		waitpid(-1, NULL, 0);
		tmp = tmp->next;
	}
	return (0);
}
	// while (cmd)
	// {
	// 	// if(!cmd->next)
	// 	// 	handle_builtin_commands(data,  cmd);
		
	// 	if (!cmd->command_args[0]) {
	// 		cmd = cmd->next;
	// 		continue;
	// 	}
	// 	char* cmd_abs_path = get_cmd_abs_path(env, cmd->command_args[0]);
	// 	check_and_handle_command( cmd,  env); // error diyal commands and permission
	// 	// we have a pipe
	// 	if (cmd->next)
	// 	{
	// 		pipe(pipefd);
	// 		cmd->out = pipefd[1];
	// 		cmd->next->in = pipefd[0];
	// 	}
	// 	// check for redirections
	// 	if (cmd->i_redir == IO_INPUT) // <
	// 	{
	// 		int fd = open(cmd->input_filename, O_RDONLY);
	// 		cmd->in = fd;
	// 	}
	// 	if (cmd->o_redir == IO_OUTPUT)// >
	// 	{
	// // attetion create the file in parser
	// 		int fd = open(cmd->output_filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	// 		close(pipefd[1]);
	// 		cmd->out = fd;
	// 	}
	// 	if (cmd->o_redir == IO_APPEND) // >>
	// 	{
	// 		int fd = open(cmd->output_filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
	// 		cmd->out = fd;
	// 	}
	// 	child_pid = fork();
	// 	if (!child_pid)
	// 	{
	// 		if (cmd->out != 1)
	// 		{
	// 			dup2(cmd->out, 1);
	// 			// 1 is now pointing at cmd->out, cmd->out is not needed anymore
	// 			close(cmd->out);
	// 		}
	// 		if (cmd->in != 0)
	// 		{
	// 			dup2(cmd->in, 0);
	// 			// same thing above, cmd->in is not needed anymore
	// 			close(cmd->in);
	// 		}
	// 		execve(cmd_abs_path, cmd->command_args, convert_env_to_arr(env));
	// 	}
	// 	if (cmd->out != 1)
	// 		close(cmd->out);
	// 	if (cmd->in != 0)
	// 		close(cmd->in);
	// 	cmd = cmd->next;

