/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:46:21 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/17 07:13:09 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

int	bult_echo(t_commands *cmd)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = false;
	while (cmd->command_args[i] && cmd->command_args[i][0] == '-'
		&& cmd->command_args[i][1] == 'n')
	{
		j = 1;
		while (cmd->command_args[i][j] == 'n')
			j++;
		if (cmd->command_args[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	print_lines(i, cmd->command_args, STDOUT_FILENO);
	if (n_option == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
