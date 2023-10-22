/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:54:38 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/22 20:59:22 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_setenv(char *var, char *value, t_env *env)
{
	char	*tmp;
	char	*new;
	t_env	*tmp_env;

	if (!var)
		return (0);
	if (!value)
		new = ft_strdup(var);
	else
	{
		tmp = ft_strjoin(var, "=");
		new = ft_strjoin(tmp, value);
		free(tmp);
	}
	if (!ft_search_set(new, var, env))
		return (0);
	tmp_env = ft_lstnew(new);
	ft_lstadd_back(&env, tmp_env);
	return (0);
}

int	check_the_number(char *str)
{
	if (!str)
		return (0);
	if (*str && ft_strchr("-+", *str))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
