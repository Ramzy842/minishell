/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:14:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 23:34:13 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**dup_env(char **envp)
{
	int		x;
	char	**ptr;

	x = 0;
	ptr = NULL;
	while (envp[x])
		x++;
	ptr = ft_calloc((x + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	x = 0;
	while (envp[x])
	{
		ptr[x] = ft_strdup(envp[x]);
		if (!ptr[x])
			return (NULL);
		x++;
	}
	ptr[x] = NULL;
	return (ptr);
}
