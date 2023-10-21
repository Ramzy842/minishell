/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:11:42 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 22:44:33 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

char	**realloc_arr(char **old_arr, int increment)
{
	int		x;
	char	**new_arr;

	x = 0;
	while (old_arr[x])
		x++;
	new_arr = malloc(sizeof(char *) * (x + increment));
	ft_memset(new_arr, 0, sizeof(char *) * (x + increment));
	x = 0;
	while (old_arr[x])
	{
		new_arr[x] = ft_strdup(old_arr[x]);
		x++;
	}
	new_arr[x] = NULL;
	x = 0;
	while (old_arr[x])
	{
		free(old_arr[x]);
		x++;
	}
	free(old_arr);
	return (new_arr);
}
