/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:27:20 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 10:50:49 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	handle_args(t_commands *tmp, int *x, t_data *data)
{
	tmp->command_args = realloc_arr(tmp->command_args, 2);
	tmp->command_args[*x] = ft_strdup(data->lexer_list->str);
	data->lexer_list = data->lexer_list->next;
	(*x)++;
}
