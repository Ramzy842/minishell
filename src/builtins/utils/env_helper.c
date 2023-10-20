/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 06:07:10 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/19 13:00:08 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../minishell.h"

int bult_env(t_env *env)
{
    t_env *tmp = env;

    while (tmp)
    {
        if (tmp->key && tmp->value)
        {
            char *env_var = ft_strjoin(tmp->key, "=");
            char *env_var_with_value = ft_strjoin(env_var, tmp->value);
            ft_putendl_fd(env_var_with_value, 1);
            free(env_var);
            free(env_var_with_value);
        }
        tmp = tmp->next;
    }
    return 0;
}
