/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/21 00:50:07 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	initialize_data(t_data *data)
{
	data->shell_input = NULL;
	data->commands = NULL;
	data->envp = NULL;
	data->lexer_list = NULL;
	data->reset = 0;
	data->pid = NULL;
	data->heredoc = 0;
	return (1);
}
