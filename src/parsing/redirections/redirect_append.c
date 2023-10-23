/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:58:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 08:58:51 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	redirect_append(t_commands *tmp, t_data *data, t_env *env, int status)
{
	(void)env;
	if (tmp->output_filename)
		free(tmp->output_filename);
	if (data->lexer_list->next)
		tmp->output_filename = 
			ft_strdup(expand_variables(
					remove_quotes(data->lexer_list->next->str), env, status));
	tmp->o_redir = IO_APPEND;
	if (open(tmp->output_filename, O_CREAT | O_RDWR | O_APPEND, 0644) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", STDERR_FILENO);
		return (0);
	}
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
	return (1);
}
