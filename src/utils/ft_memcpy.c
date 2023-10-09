/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:16:39 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/08 12:16:49 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	x;
	char	*dst1;
	char	*src1;

	dst1 = (char *)dst;
	src1 = (char *)src;
	x = 0;
	if (dst1 == NULL && src1 == NULL && n > 0)
	{
		return (NULL);
	}
	while (x < n)
	{
		dst1[x] = src1[x];
		x++;
	}
	return (dst1);
}