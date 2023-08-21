/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:56:30 by rchahban          #+#    #+#             */
/*   Updated: 2023/08/21 15:59:03 by rchahban         ###   ########.fr       */
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
	str = malloc(x + 1);
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