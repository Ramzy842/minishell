/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:55:50 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/11 19:56:06 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	x;
	char	*str;

	x = 0;
	str = (char *)s;
	if (n == 0)
		return ;
	while (x < n)
	{
		str[x] = '\0';
		x++;
	}
}