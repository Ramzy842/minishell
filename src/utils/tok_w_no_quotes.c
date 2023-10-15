/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_w_no_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:39:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/15 02:42:13 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**tok_w_no_quotes(char **args)
{
	char	**tokens;
	int		x;

	tokens = malloc(sizeof(char *) * (ft_strlen_2d(args) + 1));
	x = 0;
	while (args[x])
	{
		tokens[x] = remove_double_quotes(args[x]);
		x++;
	}
	tokens[x] = NULL;
	return (tokens);
}
