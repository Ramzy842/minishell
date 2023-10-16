/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayy_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 10:46:09 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/15 10:46:26 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}
