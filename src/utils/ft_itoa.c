/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 01:34:06 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 01:34:49 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_length(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*handle_zero(char *ptr)
{
	ptr = malloc(2);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		x;
	char	*ptr;
	long	number;

	number = (long )n;
	ptr = NULL;
	if (number == 0)
		return (handle_zero(ptr));
	ptr = malloc(sizeof(char) * (get_length(number) + 1));
	if (!ptr)
		return (0);
	x = get_length(number);
	ptr[x] = '\0';
	if (number < 0)
		number = number * -1;
	x--;
	while (number != 0)
	{
		ptr[x] = (number % 10) + 48;
		number = number / 10;
		x--;
	}
	ptr[x] = '-';
	return (ptr);
}
