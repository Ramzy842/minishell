/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:11:22 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 12:14:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	size_t			x;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	x = 0;
	while (x < length && (str1[x] != '\0' || str2[x] != '\0'))
	{
		if (str1[x] != str2[x])
		{
			return (str1[x] - str2[x]);
		}
		x++;
	}
	return (0);
}
