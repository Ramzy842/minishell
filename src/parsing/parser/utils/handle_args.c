/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:27:20 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 10:53:32 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	handle_args(t_commands *tmp, int *x, t_data *data, t_env *env, int status)
{
	tmp->command_args = realloc_arr(tmp->command_args, 2);
	if (data->lexer_list->str[0] == '\''
		&& data->lexer_list->str[ft_strlen(data->lexer_list->str) - 1] == '\'')
		tmp->command_args[*x]
			= ft_strdup(remove_quotes(data->lexer_list->str));
	else
		tmp->command_args[*x]
			= ft_strdup(expand_variables(
					remove_quotes(data->lexer_list->str), env, status));
	data->lexer_list = data->lexer_list->next;
	(*x)++;
}
