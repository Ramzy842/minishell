/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:18:05 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/21 13:58:27 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_errors(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (1);
}

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

static int	ft_search_set(char *new, char *var, t_env *tmp_env)
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

static int	check_the_number(char *str)
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
