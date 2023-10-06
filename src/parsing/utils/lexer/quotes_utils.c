/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 08:30:07 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/02 15:58:12 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

int find_matching_quote(char *line, int x, int *num_del, char del)
{
	int	y;

    y = x + 1;
    *num_del = *num_del + 1;

    while (line[y] != '\0' && line[y] != del)
        y++;
    if (line[y] == del)
        *num_del = *num_del + 1;
    return (y - x);
}

int quotes_are_matching(char *line)
{
    int	index; 
    int	single_quotes;
    int	double_quotes;

	index = 0;
	single_quotes = 0;
	double_quotes = 0;
    while (line[index] != '\0')
	{
        if (line[index] == '"')
            index = index + find_matching_quote(line, index, &double_quotes, '"');
        if (line[index] == '\'')
            index = index + find_matching_quote(line, index, &single_quotes, '\'');
        index++;
    }
    if ((double_quotes > 0 && double_quotes % 2 != 0)
		|| (single_quotes > 0 && single_quotes % 2 != 0))
        return (0);
    return (1);
}

int	handle_quotes(int x, char *str, char del)
{
	int	y;

	y = 0;
	if (str[x + y] == del)
	{
		y++;
		while (str[x + y] != del && str[x + y])
			y++;
		y++;
	}
	return (y);
}