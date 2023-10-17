/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:47:53 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 18:22:32 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	redirect_heredoc(t_commands* tmp, t_data *data)
{
	if (tmp->input_filename)
		free(tmp->input_filename);
	tmp->input_filename = ft_strdup(remove_quotes(data->lexer_list->next->str));
	tmp->i_redir = IO_HEREDOC;
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
}