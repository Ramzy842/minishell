/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 07:35:27 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/30 07:35:37 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	x;

	x = 0;
	while (s[x] != '\0')
	{
		ft_putchar_fd(s[x], fd);
		x++;
	}
	ft_putchar_fd('\n', fd);
}