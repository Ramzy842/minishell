/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:05:36 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/22 22:01:19 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_var(char *var)
{
	if (!var || !*var)
	{
		return (1);
	}
	if (!ft_isalpha(*var) && *var != '_')
	{
		return (1);
	}
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (1);
		var++;
	}
	return (0);
}

void	set_env_variable(char *var, char *value, t_env *env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			if (value)
				tmp->value = ft_strdup(value);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	env = create_and_insert_env_variable(var, value, env, prev);
}
