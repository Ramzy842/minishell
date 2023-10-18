/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:09:12 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/17 19:35:03 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	count_words(const char *str)
{
	int	count;
	int	inside_quotes;
	int	x;

	count = 1;
	inside_quotes = 0;
	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '"' || str[x] == '\'' )
            inside_quotes = !inside_quotes;
		else if (!inside_quotes && (str[x] == ' '
				|| str[x] == '\n'
				|| str[x] == '\t'))
		{
            count++;
            while (str[x + 1] == ' ' || str[x + 1] == '\n'
				|| str[x + 1] == '\t')
                x++;
        }
        x++;
    }
	return (count);
}

char	**ft_split_spaces(char *s)
{
    int		x;
	int		y;
	int		start;
	char	**ptr;
	int		inside_quotes;

	x = 0;
	y = 0;
	start = 0;
	inside_quotes = 0;
	ptr = malloc((count_words(s) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[x] != '\0')
	{
        if (s[x] == '"' || s[x] == '\'')
            inside_quotes = !inside_quotes;
        if (!inside_quotes && (s[x] == ' ' || s[x] == '\n' || s[x] == '\t'))
		{
			int finish = x - 1;
            while (finish > start && (s[finish] == ' ' || s[finish] == '\n' || s[finish] == '\t'))
                finish--;
            ptr[y] = ft_substr(s, start, finish - start + 1);
            if (!ptr[y])
			{
                int i = 0;
                while (i < y)
				{
                    free(ptr[i]);
                    i++;
                }
                free(ptr);
                return NULL;
            }
            y++;
            while (s[x + 1] == ' ' || s[x + 1] == '\n' || s[x + 1] == '\t')
                x++;
            start = x + 1;
        }
        x++;
    }
	if (inside_quotes == 0
		&& (x == 0 || (s[x - 1] != ' '
			&& s[x - 1] != '\n'
			&& s[x - 1] != '\t')))
	{
        ptr[y] = ft_substr(s, start, x - start);
        if (!ptr[y])
		{
            int i = 0;
            while (i <= y)
			{
                free(ptr[i]);
                i++;
            }
            free(ptr);
            return NULL;
        }
        y++;
    }
	if (inside_quotes == 1)
    {
        ptr[y] = ft_substr(s, start - 1, x - start + 1);
        if (!ptr[y])
        {
            int i = 0;
            while (i <= y)
            {
                free(ptr[i]);
                i++;
            }
            free(ptr);
            return NULL;
        }
        y++;
    }
    ptr[y] = NULL;
    return ptr;
}
