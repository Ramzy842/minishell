/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:24:23 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 10:28:40 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_memset(void *addr, unsigned char data, int len)
{
	int				x;
	unsigned char	*uc_addy;

	x = 0;
	uc_addy = (unsigned char *)addr;
	while (x < len)
	{
		uc_addy[x] = data;
		x++;
	}
}
