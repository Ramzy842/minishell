/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:00:54 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/22 19:01:30 by mbouderr         ###   ########.fr       */
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