/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:04:11 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/21 13:26:54 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// char	**convert_env_to_arr(t_env *env)
// {
// 	int		count;
// 	t_env	*current;
// 	int		x;
// 	int		key_len;
// 	int		value_len;
// 	int		length;
// 	char	**array;

// 	count = 0;
// 	current = env;
// 	while (current != NULL)
// 	{
// 		count++;
// 		current = current->next;
// 	}
// 	array = malloc(sizeof(char *) * (count + 1));
// 	array[count] = NULL;
// 	if (!array)
// 		return (NULL);
// 	current = env;
// 	x = 0;
// 	while (current != NULL)
// 	{
// 		key_len = ft_strlen(current->key);
// 		value_len = ft_strlen(current->value);
// 		length = key_len + value_len + 2;
// 		array[x] = malloc(sizeof(char) * length);
// 		if (!array[x])
// 			return (NULL);
// 		ft_strncpy(array[x], current->key, key_len);
// 		array[x][key_len] = '=';
// 		ft_strncpy(array[x] + key_len + 1, current->value, value_len);
// 		array[x][length - 1] = '\0';
// 		current = current->next;
// 		x++;
// 	}
// 	return (array);
// }

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
