/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:11:42 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:11:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

char	**realloc_arr(char** old_arr, int increment)
{
	int i = 0;
	while (old_arr[i])
		i++;
	char** new_arr = malloc(sizeof(char*) * (i + increment));
	ft_memset(new_arr, 0, sizeof(char*) * (i + increment));
	i = 0;
	while (old_arr[i])
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	i = 0;
	while (old_arr[i])
	{
		free(old_arr[i]);
		i++;
	}
	free(old_arr);
	return new_arr;
}