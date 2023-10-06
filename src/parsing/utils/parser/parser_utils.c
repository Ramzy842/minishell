/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:27:20 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/02 15:56:19 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void update_pipes_count(t_data *data)
{
	t_lexer *current;

	data->pipes = 0;
	current = data->lexer_list;
	while(current)
	{
		if (current->token == PIPE)
			data->pipes++;
		current = current->next;
	}
}