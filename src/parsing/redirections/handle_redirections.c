/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:49:40 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 01:40:42 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	handle_redirections(t_data *data, t_commands *tmp, t_env *env, int status)
{
	while (data->lexer_list && is_metachar(data->lexer_list->str))
	{
		if (*data->lexer_list->str == '|')
			break ;
		if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<"))
		{
			if (!redirect_input(tmp, data, env, status))
				return (0);
		}
		if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<<"))
			redirect_heredoc(tmp, data, env, status);
		if (data->lexer_list && !ft_strcmp(data->lexer_list->str, ">>"))
			if (!redirect_append(tmp, data, env, status))
				return (0);
		if ((data->lexer_list && !ft_strcmp(data->lexer_list->str, ">")))
		{
			if (!redirect_output(tmp, data, env, status))
				return (0);
		}
	}
	return (1);
}
