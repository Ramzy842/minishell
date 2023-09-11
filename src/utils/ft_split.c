/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:09:12 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/11 05:07:40 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static int	count_words(char *str, char c)
// {
// 	int	count;
// 	int	x;

// 	count = 1;
// 	x = 0;
// 	while (str[x] != 0 && str[x] == c)
// 		x++;
// 	while (str[x] != '\0')
// 	{
// 		if (((str[x] == c && str[x + 1] != c && str[x + 1] != '\"')) && str[x + 1] != '\0')
// 			count++;
// 		x++;
// 	}
// 	return (count);
// }

// char	**ft_split(char *s, char c)
// {
// 	int		x;
// 	int		y;
// 	int		finish;
// 	int		start;
// 	char	**ptr;

// 	x = 0;
// 	y = 0;
// 	ptr = malloc((count_words(s, c) + 1) * sizeof(char *));
// 	if (!ptr)
// 		return (0);
// 	while (s[x] != '\0')
// 	{
// 		if ((s[x] == '\"' && (s[x + 1] == c || s[x + 1] == '\"')))
// 			start = x;
// 		else if ((s[x] == '\"' && (s[x + 1] == c || s[x + 1] == '\"')))
// 			start = x;
// 		if (( (s[x] != c && s[x] != '\"') && (s[x + 1] == c  || s[x + 1] == '\"' || s[x + 1] == '\0')))
// 		{
// 			finish = x;
// 			ptr[y] = ft_substr(s, start, finish - start + 1);
// 			y++;
// 		}
// 		x++;
// 	}
// 	ptr[y] = NULL;
// 	return (ptr);
// }

static int	count_words(const char *str, char c)
{
	int	count;
	int	x;

	count = 1;
	x = 0;
	while (str[x] != 0 && str[x] == c)
		x++;
	while (str[x] != '\0')
	{
		if (str[x] == c && str[x + 1] != c && str[x + 1] != '\0')
			count++;
		x++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	int		x;
	int		y;
	int		finish;
	int		start;
	char	**ptr;

	x = 0;
	y = 0;
	ptr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	while (s[x] != '\0')
	{
		if (s[x] != c && (s[x - 1] == c || x == 0))
			start = x;
		if (s[x] != c && (s[x + 1] == c || s[x + 1] == '\0'))
		{
			finish = x;
			ptr[y] = ft_substr(s, start, finish - start + 1);
			y++;
		}
		x++;
	}
	ptr[y] = NULL;
	return (ptr);
}

