/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:50:57 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/20 22:23:02 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	ft_check_if_var(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}

static int	env_varcmp(void *content, void *data_ref)
{
	t_env	*env_var;
	char	*var_name;

	env_var = (t_env *)content;
	var_name = (char *)data_ref;
	return (ft_strcmp(env_var->key, var_name));
}

static int	remove_node(t_env **env, t_env *prev, t_env *tmp)
{
	if (prev)
	{
		prev->next = tmp->next;
	}
	else
	{
		*env = tmp->next;
	}
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	return (1);
}

int	ft_lstremove_if(t_env **env, char *var_name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (env_varcmp(tmp, var_name) == 0)
		{
			return (remove_node(env, prev, tmp));
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	bult_unset(t_commands *cmd, t_env *env)
{
	int	i;

	i = 1;
	while (cmd->command_args[i])
	{
		if (ft_check_if_var(cmd->command_args[i]))
			ft_errors("unset", "not a valid identifier");
		else
			ft_lstremove_if(&env, cmd->command_args[i]);
		i++;
	}
	return (0);
}
