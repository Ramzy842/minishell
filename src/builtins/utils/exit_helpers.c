/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:18:05 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/17 02:06:09 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


int	ft_errors(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (1);
}

static int	check_the_number(char *str)
{
	if (!str)
		return (0);
	if (*str && ft_strchr("-+", *str))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	bult_exit(char **args)
{

	if (args[1] && args[2])
	{
		ft_errors("exit", "too many arguments");
		return (1);
	}
	if (check_the_number(args[1]))
	{
		ft_errors (args[0], "numeric argument required");
		exit(255);
	}
	if (args[1])
		exit(ft_atoi(args[1]));
	exit(0);
	return (0);
}

