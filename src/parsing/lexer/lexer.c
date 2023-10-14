/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 03:09:35 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 03:36:17 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	skip_spaces(char *str, int x)
{
	int	y;

	y = 0;
	while ((str[x + y] == ' ' || (str[x + y] > 8 && str[x + y] < 14)))
		y++;
	return (y);
}


int	tokens_reader(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->shell_input[x])
	{
		y = 0;
		x += skip_spaces(data->shell_input, x);
		if (extract_token(data->shell_input[x]))
			y = handle_token(data->shell_input, x, &data->lexer_list);
		else
			y = handle_words(x, data->shell_input, &data->lexer_list);
		if (y < 0)
			return (0);
		x = x + y;
	}
	return (1);
}
