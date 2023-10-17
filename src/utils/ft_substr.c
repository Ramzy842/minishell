/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:09:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 12:11:01 by rchahban         ###   ########.fr       */
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
	substr = (char *)malloc((len + 1) * sizeof(char));
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
