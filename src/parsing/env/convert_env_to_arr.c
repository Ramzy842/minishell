/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:04:11 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:04:42 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char** convert_env_to_arr(t_env* env)
{
    int count = 0;
    t_env* current = env;
    
    // Count the number of key-value pairs in the linked list.
    while (current != NULL)
	{
        count++;
        current = current->next;
    }
    // Allocate memory for the char** array.
    char** array = malloc(sizeof(char*) * (count + 1));
	array[count] = NULL;
    if (!array)
		return (NULL);
    current = env;
    int i = 0;
    // Traverse the linked list and convert key-value pairs to strings.
    while (current != NULL)
	{
		int key_len = ft_strlen(current->key);
        int value_len = ft_strlen(current->value);
        int length = key_len + value_len + 2;  // +2 for '=' and null-terminator
        array[i] = (char*)malloc(sizeof(char) * length);

        if (!array[i])
			return (NULL);
        // Copy the key and value into the string in the format "key=value."
        ft_strncpy(array[i], current->key, key_len);
        array[i][key_len] = '=';
        ft_strncpy(array[i] + key_len + 1, current->value, value_len);
        array[i][length - 1] = '\0';

        // Move to the next key-value pair.
        current = current->next;
        i++;
    }
    return (array);
}