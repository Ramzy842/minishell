/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:52:39 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/22 00:34:24 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_relative_paths(char *cmd)
{
	char	*tmp2;

	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		tmp2 = cmd;
		if (!access(tmp2, F_OK))
		{
			if (!access(tmp2, X_OK))
				return (tmp2);
		}
	}
	return (NULL);
}

static char	*check_access(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (path);
	}
	return (NULL);
}

char	*get_cmd_abs_path(t_env *env, char *cmd)
{
	t_env	*path;
	char	*abs_path;
	char	**path_spl;
	int		i;
	char	*tmp1;
	char	*tmp2;

	path = get_env(env, "PATH");
	if (!path)
		return (NULL);
	abs_path = check_relative_paths(cmd);
	if (abs_path)
		return (abs_path);
	path_spl = ft_split(path->value, ':');
	if (!path_spl)
		return (NULL);
	i = 0;
	while (path_spl[i])
	{
		tmp1 = ft_strjoin(path_spl[i], "/");
		tmp2 = ft_strjoin(tmp1, cmd);
		free(tmp1);
		abs_path = check_access(tmp2);
		if (abs_path)
			return (abs_path);
		i++;
	}
	return (NULL);
}
