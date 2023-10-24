/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:09:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:23:12 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char *s, unsigned int start, int len)
{
	int		x;
	char	*substr;

	x = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substr = (char *)custom_malloc((len + 1) * sizeof(char), NULL, ALLOC, NULL);
	if (!substr)
		return (NULL);
	while (start < (unsigned int)ft_strlen(s) && x < len)
	{
		*(substr + x) = (char)s[start + x];
		x++;
	}
	*(substr + x) = '\0';
	return (substr);
}
