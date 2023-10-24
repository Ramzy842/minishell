/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:04:11 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:18:23 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_env_elements(t_env *env)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**allocate_env_array(int count)
{
	char	**array;

	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	array[count] = NULL;
	return (array);
}

char	*copy_env_to_array(char *key, char *value)
{
	int		key_len;
	int		value_len;
	int		length;
	char	*env_str;

	value_len = ft_strlen(value);
	key_len = ft_strlen(key);
	length = key_len + value_len + 2;
	env_str = malloc(sizeof(char) * length);
	if (!env_str)
		return (NULL);
	ft_strncpy(env_str, key, key_len);
	env_str[key_len] = '=';
	ft_strncpy(env_str + key_len + 1, value, value_len);
	env_str[length - 1] = '\0';
	return (env_str);
}

char	**convert_env_to_arr(t_env *env)
{
	int		count;
	char	**array;
	int		x;
	t_env	*current;

	current = env;
	x = 0;
	count = count_env_elements(env);
	array = allocate_env_array(count);
	if (!array)
		return (NULL);
	while (current != NULL)
	{
		array[x] = copy_env_to_array(current->key, current->value);
		if (!array[x])
			return (NULL);
		current = current->next;
		x++;
	}
	return (array);
}
