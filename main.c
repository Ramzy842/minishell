/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 07:15:08 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_data(t_data *data)
{
	initialize_data(data);
	data->reset = 1;
	return (1);
}

char	*show_current_path(char *working_dir)
{
	working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
	working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
	return (working_dir);
}

t_commands* gen_cmd_lst(t_data* data)
{
	t_commands*	head;
	t_commands*	tmp;
	int			x;

	head = gen_cmd_node();
	tmp = head;
	x = 0;
	while (data->lexer_list)
	{
		if (!tmp->command_args)
		{
			tmp->command_args = malloc(sizeof(char*) * 2);
			ft_memset(tmp->command_args, 0, sizeof(char*) * 2);
		}
		while (data->lexer_list && !is_metachar(data->lexer_list->str)){
			handle_args(tmp, &x, data);
		}
		while (data->lexer_list && is_metachar(data->lexer_list->str))
		{
			if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "|"))
			{
				tmp->next = gen_cmd_node();
				x = 0;
				data->lexer_list = data->lexer_list->next;
				tmp = tmp->next;
				continue;
			}
			handle_redirections(data, tmp);
		}
	}
	return (head);
}
 

int	minishell_loop(t_data *data, t_env* env)
{
	char	*temp;
	data->commands = NULL;
	data->lexer_list = NULL;
	// data->shell_input = readline("\x1b[32mminishell-> \x1b[0m");
	data->shell_input = readline("Minishell-> ");
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
		printf("error in quotes\n");
		reset_data(data);
		return (EXIT_FAILURE);	
	}
	if (!tokens_reader(data))
		return (ft_error(1, data));
	data->lexer_list = expand_lexer(data->lexer_list, env);
	data->commands = gen_cmd_lst(data);
	clear_lexer_nodes(&data->lexer_list);
    // print_cmd_lst(data->commands);
	minishell_execute(data->commands, env ,data);
	reset_data(data);
	minishell_loop(data, env);
	return (1);
}

int	extract_pwd(t_data *data)
{
	int	x;

	x = 0;
	while (data->envp[x])
	{
		if (!ft_strncmp(data->envp[x], "PWD=", 4))
			data->pwd = ft_substr(data->envp[x],
					4, ft_strlen(data->envp[x]) - 4);
		if (!ft_strncmp(data->envp[x], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[x],
					7, ft_strlen(data->envp[x]) - 7);
		x++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments.\n");
		exit(0);
	}
	initialize_data(&data);
	// extract_pwd(&data);
	// handle_envp(&data);
	t_env* env = parse_environment(dup_env(envp));
	if (!env)
		printf("no env\n");
	minishell_loop(&data, env);
	return (0);
}
