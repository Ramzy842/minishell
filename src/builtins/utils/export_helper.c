/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr <yel-hadr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:20:48 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/21 02:49:24 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

static int check_var(char *var)
{
    if (!var || !*var) {
        return (1);
    }
    if (!ft_isalpha(*var) && *var != '_') {
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

static void	set_env_variable(char *var, char *value, t_env *env)
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

static int ft_print_export(t_env *env)
{
    t_env *tmp = env;
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

int process_export_args(char *arg, t_env *env)
{
    char *var;
    char *value;

    if (ft_strchr(arg, '='))
    {
        var = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
        value = ft_strchr(arg, '=') + 1;
        if (ft_strlen(value) > 0)
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

#include <stdio.h>

int	bult_export(t_commands *cmd, t_env *env)
{
	int	i;

	i = 1;
	if (!cmd->command_args[i])
		return (ft_print_export(env));
	while (cmd->command_args[i])
	{
		printf("cmd var :%s\n", cmd->command_args[i]);
		if (process_export_args(cmd->command_args[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}
