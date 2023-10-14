/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:07:45 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:07:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char *extract_path(char **envp)
{
	int		x;
	char	*empty_str;

	x = 0;
	empty_str = NULL;
	while (envp[x])
	{
		if (!ft_strncmp(envp[x], "PATH=", 5))
			return (ft_substr(ft_strdup(envp[x]), 5, ft_strlen(envp[x]) - 5));
		x++;
	}
	empty_str = ft_strdup("\0");
	return (empty_str);
}