/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/22 00:55:54 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <dirent.h>
#include <sys/types.h>

int	exec_builtin_commands(t_commands *cmd, t_env *env)
{
	if (strcmp(cmd->command_args[0], "cd") == 0)
		buit_cd(cmd);
	if (strcmp(cmd->command_args[0], "pwd") == 0)
		ft_pwd();
	if (strcmp(cmd->command_args[0], "echo") == 0)
		bult_echo(cmd);
	if (strcmp(cmd->command_args[0], "export") == 0)
		bult_export(cmd, env);
	if (strcmp(cmd->command_args[0], "unset") == 0)
		bult_unset(cmd, env);
	if (strcmp(cmd->command_args[0], "env") == 0)
		bult_env(env);
	if (strcmp(cmd->command_args[0], "exit") == 0)
		bult_exit(cmd->command_args);
	return (0);
}
int	check_and_handle_command(t_commands *cmd, t_env *env)
{
	char	*cmd_abs_path;
	DIR		*dir;

	if ((*cmd->command_args[0] == '.' || *cmd->command_args[0] == '/'))
	{
		dir = opendir(cmd->command_args[0]);
		if (dir)
		{
			ft_errors(cmd->command_args[0], "is directory");
			cmd = cmd->next;
			return (0);
		}
	}
	cmd_abs_path = get_cmd_abs_path(env, cmd->command_args[0]);
	if ((cmd->command_args[0] && !cmd_abs_path && !check_is_builting(cmd)))
	{
		ft_errors(cmd->command_args[0], "command not found");
		cmd = cmd->next;
		return (0);
	}
	if (access(cmd_abs_path, X_OK) < 0 && cmd->command_args[0]
		&& !check_is_builting(cmd))
	{
		ft_errors(cmd->command_args[0], "permission denied");
		cmd = cmd->next;
		return (0);
	}
	return (1);
}

int	check_is_builting(t_commands *cmd)
{
	if (ft_strcmp(cmd->command_args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->command_args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->command_args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->command_args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->command_args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->command_args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->command_args[0], "exit") == 0)
		return (1);
	return (0);
}

char	*check_abs_path(char *cmd)
{
	char	*path;

	if ((cmd[0] == '.' && cmd[0] == '/') || cmd[0] == '/')
		return (path = &cmd[0]);
	else
		return (NULL);
}

int	minishell_execute(t_commands *cmd, t_env *env, t_data *data)
{
	int original_fd[2];
	int tmp_fd;
	int pid;
	char *path;
	int status;
	int i;
	int pipefd[2];

	g_signal = 1;
	(void)*data;
	tmp_fd = -1;
	if (!cmd || !cmd->command_args || !cmd->command_args[0])
		return (0);
	check_and_handle_command(cmd, env);
	original_fd[0] = dup(0);
	original_fd[1] = dup(1);
	if (!cmd->next && !ft_redir(cmd))
	{
		if (check_is_builting(cmd))
			exec_builtin_commands(cmd, env);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				path = get_cmd_abs_path(env, cmd->command_args[0]);
				execve(path, cmd->command_args, convert_env_to_arr(env));
				exit(EXIT_FAILURE);
			}
			else if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			waitpid(pid, &status, 0);
		}
		dup2(original_fd[0], 0);
		dup2(original_fd[1], 1);
	}
	if (cmd->next)
	{
		i = 0;
		while (cmd)
		{
			pipe(pipefd);
			pid = fork();
			if (pid == 0)
			{
				if (i == 0)
					dup2(pipefd[1], 1);
				else if (i > 0 && cmd->next)
				{
					dup2(tmp_fd, 0);
					dup2(pipefd[1], 1);
				}
				else if (!cmd->next)
					dup2(tmp_fd, 0);
				ft_redir(cmd);
				close(pipefd[0]);
				close(pipefd[1]);
				check_and_handle_command(cmd, env);
				if (check_is_builting(cmd))
					exec_builtin_commands(cmd, env);
				else
				{
					if ((cmd->command_args[0][0] == '.'
							&& cmd->command_args[0][0] == '/')
						|| cmd->command_args[0][0] == '/')
					{
						path = cmd->command_args[0];
					}
					else
						path = get_cmd_abs_path(env, cmd->command_args[0]);
					execve(path, cmd->command_args, convert_env_to_arr(env));
					exit(1);
				}
				exit(1);
			}
			else if (pid > 0)
			{
				if (tmp_fd > 2)
					close(tmp_fd);
				if (cmd->next)
					tmp_fd = pipefd[0];
				close(pipefd[1]);
			}
			i++;
			cmd = cmd->next;
		}
	}
	dup2(original_fd[0], 0);
	dup2(original_fd[1], 1);
	while (wait(NULL) > 0);
	g_signal = 0;
	return (0);
}