/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:30:57 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <dirent.h>
#include <sys/types.h>

int	check_if_its_a_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_errors(path, "is directory");
		return (0);
	}
	return (1);
}

int	ft_child(t_commands *cmd, t_env *env, int *pipefd, int tmp_fd)
{
	char	*path;
	int		status;

	ft_redir(cmd, pipefd, tmp_fd);
	if (check_is_builting(cmd))
		exec_builtin_commands(cmd, env);
	else
	{
		status = check_and_handle_command(cmd, env);
		if (status)
			exit(status);
		path = get_cmd_abs_path(env, cmd->command_args[0]);
		if (!path)
			exit(127);
		execve(path, cmd->command_args, convert_env_to_arr(env));
	}
	exit(EXIT_FAILURE);
}

int	ft_pipe(t_commands *cmd, t_env *env)
{
	int	pipefd[2];
	int	pid;
	int	tmp_fd;

	tmp_fd = 0;
	while (cmd)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			ft_child(cmd, env, pipefd, tmp_fd);
		else if (pid > 0)
		{
			if (tmp_fd)
				close(tmp_fd);
			tmp_fd = pipefd[0];
			close(pipefd[1]);
		}
		cmd = cmd->next;
	}
	close(tmp_fd);
	return (pid);
}

int	ft_wait_for_child(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	g_signal = 0;
	return (ft_status(status));
}

int	minishell_execute(t_commands *cmd, t_env *env, t_data *data)
{
	int	original_fd[2];
	int	pid;
	int	status;

	g_signal = 1;
	(void)*data;
	if (!cmd || !cmd->command_args)
		return (0);
	ft_save_stdin_stdout(&original_fd[0], &original_fd[1]);
	if (!cmd->next)
	{
		status = ft_exec_one(cmd, env);
		ft_reset_stdin_stdout(&original_fd[0], &original_fd[1]);
		return (status);
	}
	pid = ft_pipe(cmd, env);
	ft_reset_stdin_stdout(&original_fd[0], &original_fd[1]);
	status = ft_wait_for_child(pid);
	return (status);
}
