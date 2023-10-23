/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 22:25:32 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	reset_data(t_data *data, t_env *env, int status)
{
	if (data->lexer_list)
		clear_lexer_nodes(&data->lexer_list);
	if (data->commands)
		clear_command_nodes(&data->commands);
	if (data->shell_input)
		free(data->shell_input);
	initialize_data(data);
	data->reset = 1;
	minishell_loop(data, env, status);
	return (1);
}

int	ft_save_stdin_stdout(int *save_stdin, int *save_stdout)
{
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	return (1);
}

void	ft_reset_stdin_stdout(int *save_stdin, int *save_stdout)
{
	dup2(*save_stdin, STDIN_FILENO);
	dup2(*save_stdout, STDOUT_FILENO);
	close(*save_stdin);
	close(*save_stdout);
}

void	finalize_environment(int *fd)
{
	if (g_signal == -1)
		g_signal = 0;
	ft_save_stdin_stdout(&fd[0], &fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_env	*env;

	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments.\n");
		exit(0);
	}
	// signal(SIGINT, ft_handler);
	// signal(SIGQUIT, SIG_IGN);
	g_signal = 0;
	initialize_data(&data);
	env = parse_environment(dup_env(envp));
	if (!env)
		return (1);
	minishell_loop(&data, env, 0);
	return (0);
}
