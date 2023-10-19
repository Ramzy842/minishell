/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:27:20 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/19 10:06:00 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	handle_args(t_commands *tmp, int *x, t_data *data, t_env *env)
{
	(void)env;
	tmp->command_args = realloc_arr(tmp->command_args, 2);
	// tmp->command_args[*x] = ft_strdup(remove_quotes(data->lexer_list->str));
	// printf("%s\n", expand_variables(remove_quotes(data->lexer_list->str), env));
	tmp->command_args[*x] = ft_strdup(expand_variables(remove_quotes(data->lexer_list->str), env));
	data->lexer_list = data->lexer_list->next;
	(*x)++;
}
