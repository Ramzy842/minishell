/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:14:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:15:18 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**dup_env(char **envp)
{
	int		x;
	char	**ptr;

	x = 0;
	ptr = NULL;
	// count number of strs
	while (envp[x])
		x++;
	// allocate memo for strs
	ptr = ft_calloc((x + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	// dup each str in  the envp to the ptr
	x = 0;
	while (envp[x])
	{
		ptr[x] = ft_strdup(envp[x]);
		if (!ptr[x])
		{
			free_arr(ptr);
			return (NULL);
		}
		x++;
	}
	ptr[x] = NULL;
	return (ptr);
}
