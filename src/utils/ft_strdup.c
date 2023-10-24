/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:56:30 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:27:21 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*p;
	int		x;

	x = 0;
	while (s1[x])
		x++;
	str = custom_malloc(x+1, NULL, ALLOC , NULL);
	if (str == 0)
	{
		return (str);
	}
	p = str;
	x = 0;
	while (s1[x])
	{
		p[x] = s1[x];
		x++;
	}
	p[x] = '\0';
	return (str);
}
