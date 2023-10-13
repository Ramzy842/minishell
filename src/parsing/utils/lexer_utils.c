/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 03:10:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/13 10:57:06 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

int	handle_words(int x, char *str, t_lexer **lexer_list) // had function fiha le3ba 
/// test case ||echo hello | tr "$" "o" | cat -e
{
	int		y;
	char	*word;

	y = 0;
	while (str[x + y] && !(extract_token(str[x + y])))
	{
		y += handle_quotes(x + y, str, '"');
		y += handle_quotes(x + y, str, '\'');
		if ((str[x + y] == ' ' || (str[x + y] > 8 && str[x + y] < 14)))
			break ;
		else
			y++;
	}
	word = ft_substr(str, x, y);
	if (!add_node(word, 0, lexer_list))
		return (-1);
	return (y);
}

int	handle_token(char *str, int x, t_lexer **lexer_list)
{
	t_tokens	token;

	token = extract_token(str[x]);
	if (token == OUTPUT && extract_token(str[x + 1]) == OUTPUT)
	{
		if (!add_node(NULL, APPEND, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == INPUT && extract_token(str[x + 1]) == INPUT)
	{
		if (!add_node(NULL, HEREDOC, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}	
	return (0);
}