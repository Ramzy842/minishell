/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:10:52 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:27:23 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_with_str(char *ptr, char *str, int *x, int *y)
{
	while (*y < ft_strlen(str))
	{
		ptr[*x] = str[*y];
		(*x)++;
		(*y)++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	ptr = custom_malloc(((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char)) + 1, NULL, ALLOC,NULL);
	if (ptr == 0)
		return (ptr);
	x = 0;
	y = 0;
	fill_with_str(ptr, s1, &x, &y);
	y = 0;
	fill_with_str(ptr, s2, &x, &y);
	ptr[x] = '\0';
	return (ptr);
}
