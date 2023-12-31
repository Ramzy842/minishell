/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 03:22:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:20:12 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_lexer	*create_lexer_node(char *str, int token)
{
	t_lexer		*new_node;
	static int	idx = 0;

	new_node = custom_malloc(sizeof(t_lexer), NULL, ALLOC, NULL);
	if (!new_node)
		return (0);
	new_node->str = str;
	new_node->token = token;
	new_node->id = idx++;
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_lexer	**list, t_lexer *new_node)
{
	t_lexer	*temp;

	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

int	add_node(char *str, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = create_lexer_node(str, token);
	if (!node)
		return (0);
	append_node(lexer_list, node);
	return (1);
}

void	remove_lexer_node(t_lexer **lst, int key)
{
	t_lexer	*current;
	t_lexer	*start;

	start = *lst;
	current = start;
	if ((*lst)->id == key)
	{
		delete_first_lexer_node(lst);
		return ;
	}
	while (current && current->id != key)
		current = current->next;
	free_lexer_node(&current);
	*lst = start;
}
