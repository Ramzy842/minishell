/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:54:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/25 09:50:55 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int		contains_equal(char *str)
{
	if (ft_strnstr(str, "=", ft_strlen(str)))
	{
		printf("%s is a possible expansion\n", str);
		//return (1);
	}
	return (0);
}

void	expander(t_command_pipeline *pipeline, char **full_command)
{
	int x = 0;
	int y = 0;
	(void) full_command;
	//char **vars = malloc(sizeof(char *) * (ft_strlen_2d(full_command)));

	while (x < pipeline->number_of_commands)
	{
		contains_equal(pipeline->commands[x].command);
		y = 0;
		while (pipeline->commands[x].args[y])
		{
			contains_equal(pipeline->commands[x].args[y]);
			y++;
		}
		x++;
	}
}