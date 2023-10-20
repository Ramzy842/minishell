/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:02:27 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 11:10:08 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env* parse_environment(char **env)
{
    t_env* env_list = NULL;
    
    int i = 0;
    while (env[i] != NULL)
	{
        char* equals = ft_strchr(env[i], '=');
        if (equals != NULL) {
            size_t key_len = equals - env[i];
            char key[key_len + 1];
            ft_strncpy(key, env[i], key_len);
            key[key_len] = '\0';
            char* value = equals + 1;
			// free(equals);
            // Add the key-value pair to the linked list
            env_list = add_env(env_list, key, value);
        }
        i++;
    }
    return (env_list);
}