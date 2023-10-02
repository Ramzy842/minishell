/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:05:23 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/30 06:11:18 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int		x;
	char	*str2;

	x = 0;
	str2 = (char *)str;
	while (x < ft_strlen(str2))
	{
		if (str2[x] == (char )c)
			return (((char *) str2) + x);
		x++;
	}
	if (str2[x] == (char )c)
		return (((char *)str2) + x);
	return (NULL);
}