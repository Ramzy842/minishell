/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:57:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/18 05:07:41 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	redirect_output(t_commands* tmp, t_data *data)
{
	if (tmp->output_filename)
		free(tmp->output_filename);
	if (data->lexer_list->next)
	{
		tmp->output_filename = ft_strdup(remove_quotes(data->lexer_list->next->str));
		data->lexer_list = data->lexer_list->next;
	}
	tmp->o_redir = IO_OUTPUT;
	if (open(tmp->output_filename, O_CREAT | O_RDWR | O_TRUNC, 0644) == -1)
	{
        ft_putstr_fd("minishell: error creating file\n", STDERR_FILENO);
        return (0);
    }
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
	return (1);
}