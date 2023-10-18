/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 03:10:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/18 03:37:35 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

t_tokens	extract_token(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (OUTPUT);
	else if (c == '<')
		return (INPUT);
	return (0);
}

int	handle_words(int x, char *str, t_lexer **lexer_list)
{
	int		y;
	char	*word;

	y = 0;
	while (str[x + y] && !(extract_token(str[x + y])))
	{
		y += handle_quotes(x + y, str, '"');
		y += handle_quotes(x + y, str, '\'');
		if (str && (str[x + y] == ' ' || (str[x + y] > 8 && str[x + y] < 14)))
			break ;
		else
			y++;
	}
	word = ft_substr(str, x, y);
	if (!add_node(word, 0, lexer_list))
		return (-1);
	return (y);
}

// int	handle_basic_tokens(t_tokens token, t_lexer **lexer_list)
// {
// 	if (token == INPUT)
// 	{
// 		if (!add_node(ft_strdup("<"), INPUT, lexer_list))
// 			return (-1);
// 	}
// 	if (token == OUTPUT)
// 	{
// 		if (!add_node(ft_strdup(">"), OUTPUT, lexer_list))
// 			return (-1);
// 	}
// 	if (token == PIPE)
// 	{
// 		if (!add_node(ft_strdup("|"), PIPE, lexer_list))
// 			return (-1);
// 	}
// 	return (1);
// }

int	handle_token(char *str, int x, t_lexer **lexer_list)
{
	t_tokens	token;

	token = extract_token(str[x]);
	if (token == OUTPUT && extract_token(str[x + 1]) == OUTPUT)
	{
		if (!add_node(ft_strdup(">>"), APPEND, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == INPUT && extract_token(str[x + 1]) == INPUT)
	{
		if (!add_node(ft_strdup("<<"), HEREDOC, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (token == INPUT)
		{
			if (!add_node(ft_strdup("<"), INPUT, lexer_list))
				return (-1);
		}
		if (token == OUTPUT)
		{
			if (!add_node(ft_strdup(">"), OUTPUT, lexer_list))
				return (-1);
		}
		if (token == PIPE)
		{
			if (!add_node(ft_strdup("|"), PIPE, lexer_list))
				return (-1);
		}
		return (1);
	// handle_basic_tokens(token, lexer_list);
	}
	return (0);
}
