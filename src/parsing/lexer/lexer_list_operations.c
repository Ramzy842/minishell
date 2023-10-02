/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 03:22:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/01 11:24:31 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_lexer	*create_lexer_node(char *str, int token)
{
	t_lexer		*new_node;
	static int	idx = 0;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (0);
	new_node->str = str;
	new_node->token = token;
	new_node->index = idx++;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	append_node(t_lexer	**list, t_lexer *new_node)
{
	t_lexer *temp;

	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
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