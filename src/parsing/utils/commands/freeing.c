/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:23:18 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 10:35:48 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	clear_command_nodes(t_commands **list)
{
	t_commands	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->command_args)
			free_arr((*list)->command_args);
		if ((*list)->heredoc)
			free((*list)->heredoc);
		if ((*list)->input_filename)
			free((*list)->input_filename);
		if ((*list)->output_filename)
			free((*list)->output_filename);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}
