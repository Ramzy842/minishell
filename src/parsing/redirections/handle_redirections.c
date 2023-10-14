/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:49:40 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 10:49:57 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	handle_redirections(t_data *data, t_commands *tmp)
{
	while (data->lexer_list && is_metachar(data->lexer_list->str))
	{
		if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<"))
			redirect_input(tmp, data);
		else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<<"))
			redirect_heredoc(tmp, data);
		else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, ">>"))
			redirect_append(tmp, data);
		else if ((data->lexer_list && !ft_strcmp(data->lexer_list->str, ">"))
				|| (!tmp->command_args && !ft_strcmp(data->lexer_list->str,">"))) 
			redirect_output(tmp, data);
	}
}