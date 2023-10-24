/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:22:13 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:20:44 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_new_cmd_generation(t_data *data, t_commands **tmp)
{
	(*tmp)->next = gen_cmd_node();
	data->x = 0;
	data->lexer_list = data->lexer_list->next;
	*tmp = (*tmp)->next;
}

void	argumentize(t_commands *tmp, t_data *data, t_env *env, int status)
{
	if (!tmp->command_args)
	{
		tmp->command_args = custom_malloc((sizeof(char *) * 2), 
				NULL, ALLOC, NULL);
		ft_memset(tmp->command_args, 0, sizeof(char *) * 2);
	}
	while (data->lexer_list && !is_metachar(data->lexer_list->str))
		handle_args(tmp, data, env, status);
}

t_commands	*gen_cmd_lst(t_data *data, t_env *env, int status)
{
	t_commands	*head;
	t_commands	*tmp;
	int			fd[2];

	head = gen_cmd_node();
	tmp = head;
	ft_save_stdin_stdout(&fd[0], &fd[1]);
	g_signal = -1;
	while (data->lexer_list)
	{
		argumentize(tmp, data, env, status);
		while (data->lexer_list && is_metachar(data->lexer_list->str))
		{
			if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "|"))
			{
				handle_new_cmd_generation(data, &tmp);
				continue ;
			}
			if (!handle_redirections(data, tmp, env, status))
				return (NULL);
		}
	}
	finalize_environment(fd);
	return (head);
}

void	gen_cmds_and_execute(t_data *data, t_env *env, int status)
{
	data->commands = gen_cmd_lst(data, env, status);
	if (!data->commands)
	{
		status = 1;
		reset_data(data, env, status);
	}
	else
	{
		status = minishell_execute(data->commands, env, data);
		reset_data(data, env, status);
	}
}

int	minishell_loop(t_data *data, t_env *env, int status)
{
	char	*temp;

	temp = NULL;
	init_starting_props(temp, data);
	if (!data->shell_input)
		return (EXIT_SUCCESS);
	if (ft_strlen(&data->shell_input[0]) == '\0')
		return (reset_data(data, env, status));
	add_history(data->shell_input);
	if (!quotes_are_matching(data->shell_input)
		|| !tokens_reader(data)
		|| !syntaxer(data->lexer_list))
	{
		ft_putendl_fd("minishell: syntax error", STDOUT_FILENO);
		status = 1;
		reset_data(data, env, status);
		return (EXIT_FAILURE);
	}
	if (data->lexer_list)
		gen_cmds_and_execute(data, env, status);
	return (1);
}
