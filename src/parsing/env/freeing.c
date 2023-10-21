/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:09:04 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 23:30:50 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_env_list(t_env *list)
{
	t_env	*current;

	while (list != NULL)
	{
		current = list;
		list = list->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}
