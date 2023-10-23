/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:57:56 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 01:40:06 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	redirect_input(t_commands *tmp, t_data *data, t_env *env, int status)
{
	(void)env;
	if (tmp->input_filename)
		free(tmp->input_filename);
	tmp->input_filename = ft_strdup(
			expand_variables(
				remove_quotes(data->lexer_list->next->str), env, status));
	tmp->i_redir = IO_INPUT;
	if (open(tmp->input_filename, O_RDONLY) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", STDERR_FILENO);
		return (0);
	}
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
	return (1);
}
