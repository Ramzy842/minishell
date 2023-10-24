/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:09:12 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:27:13 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	f_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	f_len(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (!s)
		return (NULL);
	str =  (char **)custom_malloc((sizeof(char *) * (f_count(s, c) + 1)) ,NULL, ALLOC , NULL);
	if (!str)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			str[k] = ft_substr(s + i, 0, f_len(s + i, c));
			k++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	str[k] = NULL;
	return (str);
}
