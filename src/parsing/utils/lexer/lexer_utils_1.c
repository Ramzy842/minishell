/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:14:31 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 06:14:21 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

t_lexer	*free_lexer_node(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	clear_lexer_nodes(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	delete_first_lexer_node(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	free_lexer_node(&node);
}
