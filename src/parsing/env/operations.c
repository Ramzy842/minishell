/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:09:51 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:09:56 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env* add_env(t_env* list, const char* key, const char* value)
{
    t_env* new_env = malloc(sizeof(t_env));
    if (!new_env)
		return (NULL);
    new_env->key = strdup(key);
    new_env->value = strdup(value);
    new_env->next = list;
    return new_env;
}