/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 23:59:28 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/24 05:17:49 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	exec_builtin_commands(t_commands *cmd, t_env *env)
{
	if (ft_strcmp(cmd->command_args[0], "cd") == 0)
		return (buit_cd(cmd));
	if (ft_strcmp(cmd->command_args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->command_args[0], "echo") == 0)
		return (bult_echo(cmd));
	if (ft_strcmp(cmd->command_args[0], "export") == 0)
		return (bult_export(cmd, env));
	if (ft_strcmp(cmd->command_args[0], "unset") == 0)
		return (bult_unset(cmd, env));
	if (ft_strcmp(cmd->command_args[0], "env") == 0)
		return (bult_env(env));
	if (ft_strcmp(cmd->command_args[0], "exit") == 0)
		return (bult_exit(cmd->command_args));
	return (0);
}
