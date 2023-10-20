/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:20:48 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/20 11:09:35 by mbouderr         ###   ########.fr       */
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
static int check_var(char *var) {
    if (!var)
        return (1);
    if (!ft_isalpha(*var) && *var != '_')
        return (1);
    while (*var && *var != '=') {
        if (!ft_isalnum(*var) && *var != '_')
            return (1);
        var++;
    }
    return (0);
}

static void set_env_variable(char *var, char *value, t_env *env) {
    t_env *tmp = env;

    while (tmp) {
        if (ft_strcmp(tmp->key, var) == 0) {
            if (tmp->value) {
                free(tmp->value);
            }
            tmp->value = (value) ? ft_strdup(value) : NULL;
            return; // Variable found and updated
        }
        tmp = tmp->next;
    }

    // If the variable doesn't exist, add it as a new environment variable
    t_env *new_env = malloc(sizeof(t_env));
    if (new_env) {
        new_env->key = ft_strdup(var);
        new_env->value = (value) ? ft_strdup(value) : NULL;
        new_env->next = NULL;

        // Find the last element in the linked list
        t_env *temp = env;
        while (temp && temp->next) {
            temp = temp->next;
        }

        if (temp) {
            temp->next = new_env;
        } else {
            // If the environment is empty, set the new environment as the first element
            *env = *new_env;
        }
    }
}
static int ft_print_export(t_env *env) {
    t_env *tmp = env;
    while (tmp) {
        if (tmp->value) {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(tmp->key, 1);
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(tmp->value, 1);
            ft_putstr_fd("\"\n", 1);
        }
        tmp = tmp->next;
    }
    return 0;
}

int bult_export(t_commands *cmd, t_env *env) {
    int i = 1;
    if (!cmd->command_args[i]) {
        return ft_print_export(env);
    }
    while (cmd->command_args[i]) {
        if (check_var(cmd->command_args[i])) {
            ft_errors("export", "not a valid identifier");
            return 1;
        }
        if (ft_strchr(cmd->command_args[i], '=')) {
            char *var = ft_substr(cmd->command_args[i], 0, ft_strchr(cmd->command_args[i], '=') - cmd->command_args[i]);
            char *value = ft_strchr(cmd->command_args[i], '=') + 1;
            set_env_variable(var, value, env);
            free(var);
        }
        i++;
    }
    return 0;
}