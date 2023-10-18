/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:49:40 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/18 05:24:31 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	handle_redirections(t_data *data, t_commands *tmp)
{
	while (data->lexer_list && is_metachar(data->lexer_list->str))
	{
		if (*data->lexer_list->str == '|')
			break;
		if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<"))
		{
			if (!redirect_input(tmp, data))
				return (0);
		}
		else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<<"))
		{
			redirect_heredoc(tmp, data);
		}
		else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, ">>"))
		{
			if (!redirect_append(tmp, data))
				return (0);
		}
		else if ((data->lexer_list && !ft_strcmp(data->lexer_list->str, ">"))
				|| (!tmp->command_args && !ft_strcmp(data->lexer_list->str,">")))
		{
			if (!redirect_output(tmp, data))
				return (0);	
		}	
	}
	return (1);
}
