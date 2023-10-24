/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:00:54 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/24 05:31:58 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	if (g_signal > 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		if (g_signal == -1)
		{
			close(STDIN_FILENO);
			g_signal = -2;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*check_abs_path(char *cmd)
{
	char	*path;

	if ((cmd[0] == '.' && cmd[0] == '/') || cmd[0] == '/')
		return (path = &cmd[0]);
	else
		return (NULL);
}

int	ft_status(int status)
{
	int	sig_status;

	if (WIFSIGNALED(status))
	{
		sig_status = status << 8;
		return (WEXITSTATUS(sig_status) + 128);
	}
	return (status >> 8);
}

int	ft_exec_one(t_commands *cmd, t_env *env)
{
	int		pid;
	char	*path;
	int		status;

	ft_redir(cmd, NULL, 0);
	if (*cmd->command_args && check_is_builting(cmd))
		return (exec_builtin_commands(cmd, env));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!*cmd->command_args)
				exit(0);
			status = check_and_handle_command(cmd, env);
			if (status)
				exit(status);
			path = get_cmd_abs_path(env, cmd->command_args[0]);
			execve(path, cmd->command_args, convert_env_to_arr(env));
			exit(EXIT_FAILURE);
		}
		waitpid(pid, &status, 0);
	}
	return (ft_status(status));
}

int	check_and_handle_command(t_commands *cmd, t_env *env)
{
	char	*cmd_abs_path;

	if ((*cmd->command_args[0] == '.' || *cmd->command_args[0] == '/'))
		if (!check_if_its_a_directory(cmd->command_args[0]))
			return (126);
	cmd_abs_path = get_cmd_abs_path(env, cmd->command_args[0]);
	if ((cmd->command_args[0] && !cmd_abs_path && !check_is_builting(cmd)))
	{
		ft_errors(cmd->command_args[0], "command not found");
		cmd = cmd->next;
		return (127);
	}
	if (access(cmd_abs_path, X_OK) < 0 && cmd->command_args[0]
		&& !check_is_builting(cmd))
	{
		ft_errors(cmd->command_args[0], "permission denied");
		cmd = cmd->next;
		return (126);
	}
	return (0);
}
