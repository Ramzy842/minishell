/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:12:39 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/15 08:00:02 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

int	get_list_length(void *head)
{
    int			length;
    t_lexer*	current;

	length = 0;
	current = head;
    while (current != NULL)
	{
        length++;
        current = current->next;
    }
    return (length);
}