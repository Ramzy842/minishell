/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:54:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/18 05:53:24 by rchahban         ###   ########.fr       */
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

int count_dollar_signs(char *str)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '$')
			count++;
		x++;
	}
	return (count);
}

t_lexer *expand_lexer(t_lexer* lexer_list, t_env* env)
{
    t_lexer* current = lexer_list;
    t_lexer* updated_list = NULL;
    t_lexer* updated_list_tail = NULL;
    char* dollar_sign;
	char *removed_quotes_str = NULL;

	dollar_sign = NULL;
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
		// if dollar signs > 1
		if (count_dollar_signs(current->str) > 1)
		{
			int x = 0;
			removed_quotes_str = remove_quotes(current->str);
			char **spl = ft_split(removed_quotes_str, '$');
			char *joined = malloc(1);
			joined[0] = '\0';
			while (spl[x])
			{	
				char* var_name = spl[x];
				char* var_value = find_env_var(env, var_name);
				if (var_value)
        	    	joined = ft_strjoin(joined, var_value);
				else
        	    	joined = ft_strjoin(joined, "");
				x++;
			}
			new_node->str = joined;
		}
		else // if dollar signs == 1
		{
			removed_quotes_str = remove_quotes(current->str);
			dollar_sign = ft_strchr(removed_quotes_str, '$');
			free(removed_quotes_str);
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
		}
        current = current->next;
    }
    if (updated_list_tail)
        updated_list_tail->next = NULL;
    return (updated_list);
}
