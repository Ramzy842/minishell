/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/10 18:59:15 by rchahban         ###   ########.fr       */
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

void ft_memset(void* addr, unsigned char data, int len) {
	int i = 0;
	unsigned char* uc_addy = (unsigned char*)addr; 
	while (i < len) {
		uc_addy[i] = data;
		i++;
	}
}

t_commands* gen_cmd_node() {
	t_commands* ret = malloc(sizeof(t_commands));
	ft_memset(ret, 0, sizeof(t_commands));
	return ret;
}

int is_redir_op(char* str) {
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")) {
		return 1;
	}
	return 0;
}

int is_metachar(char* str) {
	if (is_redir_op(str) || !ft_strcmp(str, "|"))
		return 1;
	return 0;
}

int calc_argv_sz(t_lexer* data) {
	int i = 0;
	while (data && !is_metachar(data->str)) {
		data = data->next;
		i++;
	}
	return i;
}

void print_cmd_lst(t_commands* cmd) {
	while (cmd) {
		int i = 0;
		printf("argv: ");
		while (cmd->command_args[i]) {
			printf("%s", cmd->command_args[i]);
			if (cmd->command_args[i + 1])
				printf(", ");
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}



t_commands* gen_cmd_lst(t_data* data) {
	t_commands* head = gen_cmd_node();
	t_commands* tmp = head;
	int i = 0;
	while (data->lexer_list) {
		int sz = calc_argv_sz(data->lexer_list);
		tmp->command_args = malloc(sizeof(char*) * calc_argv_sz(data->lexer_list) + 1);
		ft_memset(tmp->command_args, 0, sizeof(char*) * calc_argv_sz(data->lexer_list) + 1);
		while (data->lexer_list && !is_metachar(data->lexer_list->str)) {
			tmp->command_args[i] = ft_strdup(data->lexer_list->str);
			data->lexer_list = data->lexer_list->next;
			i++;
		}
		if (!ft_strcmp(data->lexer_list->str, "|")) {
			tmp->next = gen_cmd_node();
			data->lexer_list = data->lexer_list->next;
			tmp = tmp->next;
			continue;
		}
		if (is_redir_op(data->lexer_list->str) && !data->lexer_list->next)
		{
			// maybe free hna
			// syntax error
			return NULL;
		}
		if (!ft_strcmp(data->lexer_list->str, "<")) {
			if (tmp->input_filename)
				free(tmp->input_filename);
			tmp->input_filename = ft_strdup(data->lexer_list->next->str);
			data->lexer_list = data->lexer_list->next;
			tmp->i_redir = INPUT;
		}
		if (!ft_strcmp(data->lexer_list->str, "<<")) {
			data->lexer_list = data->lexer_list->next;
			tmp->i_redir = HEREDOC;
		}
		if (!ft_strcmp(data->lexer_list->str, ">>")) {
			if (tmp->output_filename)
				free(tmp->output_filename);
			tmp->output_filename = ft_strdup(data->lexer_list->next->str);
			data->lexer_list = data->lexer_list->next;
			tmp->o_redir = APPEND;
		}
		if (!ft_strcmp(data->lexer_list->str, ">")) {
			if (tmp->output_filename)
				free(tmp->output_filename);
			data->lexer_list = data->lexer_list->next;
			tmp->output_filename = ft_strdup(data->lexer_list->next->str);
			tmp->o_redir = OUTPUT;
		}
		i = 0;
	}
	return head;
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
	t_commands* cmd = gen_cmd_lst(data);

	print_cmd_lst(cmd);
	// launch_parser(data);
	// build_commands_list(&data->lexer_list, data);
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
