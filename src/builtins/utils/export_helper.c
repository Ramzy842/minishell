/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:20:48 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/24 05:22:33 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*create_env_variable(char *var, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env)
	{
		new_env->key = ft_strdup(var);
		if (value)
		{
			new_env->value = ft_strdup(value);
		}
		else
		{
			new_env->value = NULL;
		}
		new_env->next = NULL;
	}
	return (new_env);
}

t_env	*create_and_insert_env_variable(char *var, char *value, t_env *env,
		t_env *prev)
{
	t_env	*new_env;

	new_env = create_env_variable(var, value);
	if (new_env)
	{
		if (prev)
			prev->next = new_env;
		else
			env = new_env;
	}
	return (env);
}

int	ft_print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else if (tmp->key)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	process_export_args(char *arg, t_env *env)
{
	char	*var;
	char	*value;

	if (ft_strchr(arg, '='))
	{
		var = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_strchr(arg, '=') + 1;
		if (ft_strlen(value) >= 0)
		{
			set_env_variable(var, value, env);
		}
		free(var);
	}
	else
	{
		if (check_var(arg))
		{
			ft_errors("export", "not a valid identifier");
			return (1);
		}
		set_env_variable(arg, NULL, env);
	}
	return (0);
}

int	bult_export(t_commands *cmd, t_env *env)
{
	int	i;

	i = 1;
	if (!cmd->command_args[i])
		return (ft_print_export(env));
	while (cmd->command_args[i])
	{
		if (process_export_args(cmd->command_args[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}
