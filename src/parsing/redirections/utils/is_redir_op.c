/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:29:28 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 10:30:29 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

int is_redir_op(char* str)
{
	if (!ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<<"))
		return 1;
	return 0;
}