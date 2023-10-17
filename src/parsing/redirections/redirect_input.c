/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:57:56 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 18:22:13 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	redirect_input(t_commands* tmp, t_data *data)
{
	if (tmp->input_filename)
		free(tmp->input_filename);
	tmp->input_filename = ft_strdup(remove_quotes(data->lexer_list->next->str));
	tmp->i_redir = IO_INPUT;
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
}