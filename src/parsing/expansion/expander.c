/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:54:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 04:40:00 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char* find_env_var(t_env* env, char* key)
{
    t_env* current = env;
    while (current != NULL)
	{
        if (ft_strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

t_lexer *expand_lexer(t_lexer* lexer_list, t_env* env)
{
    t_lexer* current = lexer_list;
    t_lexer* updated_list = NULL;
    t_lexer* updated_list_tail = NULL;
    char* dollar_sign;

    while (current != NULL)
	{
        t_lexer* new_node = malloc(sizeof(t_lexer));
        if (!new_node)
            return (NULL);
        if (!updated_list)
		{
            updated_list = new_node;
            updated_list_tail = updated_list;
        }
		else
		{
            updated_list_tail->next = new_node;
            updated_list_tail = new_node;
        }
		dollar_sign = ft_strchr(current->str, '$');
        if (dollar_sign)
		{
            char* var_name = dollar_sign + 1;
            char* var_value = find_env_var(env, var_name);
            if (var_value)
                new_node->str = ft_strdup(var_value);
			else
                new_node->str = ft_strdup("");
        }
		else
            new_node->str = ft_strdup(current->str);
        current = current->next;
    }
    if (updated_list_tail)
        updated_list_tail->next = NULL;
    return (updated_list);
}
