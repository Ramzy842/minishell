/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:18:05 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/22 22:00:28 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_lstadd_back(t_env **env, t_env *new)
{
	t_env	*current;

	current = *env;
	if (!current)
	{
		*env = new;
		return ;
	}
	while (current)
	{
		if (current->next)
			current = current->next;
		else
		{
			current->next = new;
			break ;
		}
	}
}

int	ft_search_set(char *new, char *var, t_env *tmp_env)
{
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, var, ft_strlen(var)))
		{
			if (((char *)tmp_env->key)[ft_strlen(var)] == '=')
			{
				free(tmp_env->key);
				tmp_env->key = new;
				return (0);
			}
			else if (((char *)tmp_env->key)[ft_strlen(var)] == '\0')
			{
				free(tmp_env->key);
				tmp_env->key = new;
				return (0);
			}
		}
		tmp_env = tmp_env->next;
	}
	return (1);
}

t_env	*ft_lstnew(void *key)
{
	t_env	*ptr;

	ptr = (t_env *)(ft_calloc(sizeof(t_env), 1));
	if (!ptr)
		return (NULL);
	ptr->key = key;
	ptr->next = NULL;
	return (ptr);
}

int	bult_exit(char **args)
{
	if (args[1] && args[2])
	{
		ft_errors("exit", "too many arguments");
		return (1);
	}
	if (check_the_number(args[1]))
	{
		ft_errors(args[0], "numeric argument required");
		exit(255);
	}
	if (args[1])
		exit(ft_atoi(args[1]));
	exit(0);
	return (0);
}
