/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 07:10:58 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:17:01 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*ptr;
	size_t	x;
	size_t	l;
	size_t	n;

	if (!set || !s1)
		return (NULL);
	n = 0;
	while (ft_strchr(set, s1[n]) && s1[n])
		n++;
	l = ft_strlen(s1);
	while (n < l && ft_strchr(set, s1[l - 1]) && l > 0)
		l--;
	ptr = (char *)custom_malloc((l - n) + 1, NULL, ALLOC, NULL);
	if (!ptr)
		return (NULL);
	x = 0;
	while (n < l)
		ptr[x++] = s1[n++];
	ptr[x] = '\0';
	return (ptr);
}
