/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/09 17:41:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./src/parsing/parsing.h"

void	free_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}

int	minishell_loop(t_data *data);

void	clear_command_nodes(t_commands **lst)
{
	t_commands		*tmp;
	t_lexer			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		if (redirections_tmp)
			clear_lexer_nodes(&redirections_tmp);
		if ((*lst)->command_args)
			free_arr((*lst)->command_args);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	reset_data(t_data *data)
{
	// if (data->commands)
	// 	clear_command_nodes(&data->commands);
	// free(data->shell_input);
	// if (data->pid)
	// 	free(data->pid);
	// free_arr(data->paths);
	initialize_data(data);
	data->reset = 1;
	printf("performing reset...\n");
	minishell_loop(data);
	return (1);
}

char *show_current_path(char *working_dir)
{
	working_dir = print_current_dir();
	working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
	working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
	return (working_dir);
}

int	minishell_loop(t_data *data)
{
	// char    *working_dir = NULL;
	char	*temp;
	data->commands = NULL;
	data->lexer_list = NULL;
	data->pipes = 0;
	data->shell_input = NULL;
	//working_dir = show_current_path(working_dir);
	// data->shell_input = readline(working_dir);
	data->shell_input = readline("\x1b[32mminishell-> \x1b[0m");
	//free(working_dir);
	temp = ft_strtrim(data->shell_input, " ");
	free(data->shell_input);
	data->shell_input = temp;
	if (!data->shell_input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(&data->shell_input[0]) == '\0')
		return (reset_data(data));
	add_history(data->shell_input);
	if (!quotes_are_matching(data->shell_input))
	{
		//return (ft_error(2, data));
		printf("error in quotes\n");
		reset_data(data);
		return (EXIT_FAILURE);	
	}
	if (!tokens_reader(data))
		return (ft_error(1, data));
	//print_tokens_list(data);
	// launch_parser(data);
	// print_commands(data->commands);
	//print_commands(data->command);
	//prepare_executor(data);
	// launch_parser(data);
	build_commands_list(&data->lexer_list, data);
	// t_commands *cmds = parse_commands(data);
	// print_commands_list(data->commands);
	printf("\x1b[33mexecuting command...\x1b[0m\n");
	reset_data(data);
	return (1);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	(void) envp;
	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments.\n");
		exit(0);
	}
	//data.envp = ft_arrdup(envp);
	//find_pwd(&tools);
	initialize_data(&data);
	minishell_loop(&data);
	return (0);
}
