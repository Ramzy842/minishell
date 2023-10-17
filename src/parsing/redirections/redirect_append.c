/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:58:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 18:22:43 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	redirect_append(t_commands* tmp, t_data *data)
{
	if (tmp->output_filename)
		free(tmp->output_filename);
	if (data->lexer_list->next)
		tmp->output_filename = ft_strdup(remove_quotes(data->lexer_list->next->str));
	tmp->o_redir = IO_APPEND;
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
}
