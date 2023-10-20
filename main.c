/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/19 00:28:50 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	minishell_loop(t_data *data, t_env* env);

int	reset_data(t_data *data, t_env *env)
{
	if (data->lexer_list)
		clear_lexer_nodes(&data->lexer_list);
	if (data->commands)
	 	clear_command_nodes(&data->commands);
	free(data->shell_input);
	// if (data->pid)
	// 	free(data->pid);
	// free_arr(data->paths);
	initialize_data(data);
	data->reset = 1;
	minishell_loop(data, env);
	// printf("Performing reset...\n");
	return (1);
}

// char	*show_current_path(char *working_dir)
// {
// 	working_dir = print_current_dir();
// 	working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
// 	working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
// 	return (working_dir);
// }

t_commands* gen_cmd_lst(t_data* data)
{
	t_commands*	head;
	t_commands*	tmp;
	int			x;
	// int			redir_err = 0;

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
		while (data->lexer_list && !is_metachar(data->lexer_list->str))
			handle_args(tmp, &x, data);
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
			if (!handle_redirections(data, tmp))
			{
				// redir_err = 1;
				// break ;
				return (NULL);
			}
		}
		// if (redir_err)
		// 	retru;
	}
	return (head);
}
static char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	free(s1);
	return (res);
}

char	*remove_quotes(char *cmd)
{
	int		i;
	int		dq;
	int		sq;
	char	*res;

	i = 0;
	dq = 0;
	sq = 0;
	res = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !dq)
			sq = !sq;
		else if (cmd[i] == '\"' && !sq)
			dq = !dq;
		else
			res = ft_strjoin_char(res, cmd[i]);
		i++;
	}
	return (res);
}

int syntaxer(t_lexer *lexer)
{
	t_lexer *tmp = lexer;
	if ((tmp->token >= INPUT && tmp->token <= PIPE)
		&& get_list_length((t_lexer*)lexer) == 1)
		return (0);
	while (tmp)
	{
		if (tmp->token >= INPUT && tmp->token <= PIPE
			&& tmp->next->token >= INPUT && tmp->next->token <= PIPE)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char* remove_quotes(char* input);

t_lexer *quotes_remover(t_lexer *lexer)
{
	t_lexer *tmp = lexer;
	while (tmp)
	{
		printf("%s", remove_quotes(tmp->str));
		if (tmp->next)
			printf(", ");
		tmp = tmp->next;
	}
	printf("\n");
	return (NULL);	
}

int	minishell_loop(t_data *data, t_env* env)
{
	char	*temp = NULL;
	data->commands = NULL;
	data->lexer_list = NULL;
	// data->shell_input = readline("\x1b[32mminishell-> \x1b[0m");
	data->shell_input = readline("Minishell-> ");
	temp = ft_strtrim(data->shell_input, " ");
	free(data->shell_input);
	data->shell_input = ft_strdup(temp);
	if (!data->shell_input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(&data->shell_input[0]) == '\0')
		return (reset_data(data, env));
	add_history(data->shell_input);
	if (!quotes_are_matching(data->shell_input))
	{
		ft_putendl_fd("Syntax error", STDOUT_FILENO);
		reset_data(data, env);
		return (EXIT_FAILURE);
	}
	// puts("hoooooooh");	
	if (!tokens_reader(data))
		return (ft_error(1, data, env));
	if (!syntaxer(data->lexer_list))
	{
		ft_putstr_fd("Syntax error\n", STDERR_FILENO);
		reset_data(data, env);
	}
	// puts("heh");
	if (data->lexer_list)
	{	
		data->lexer_list = expand_lexer(data->lexer_list, env);
		// quotes_remover(data->lexer_list);
		data->commands = gen_cmd_lst(data);
		
		if (!data->commands)
			reset_data(data, env);
		else 
		{
			minishell_execute(data->commands, env ,data);
			reset_data(data, env);
		}
		// clear_lexer_nodes(&data->lexer_list);
	}
	
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



// if word is surrounded by quotes ---> remove quotes outer quotes
// Q: WHEN?
// A: after assigning the command args and redirs

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments.\n");
		exit(0);
	}
	// char	*cmd;
	// char	*res;

	// cmd = ft_strdup("l\"s\" echo");
	// res = remove_quotes(cmd);
	// printf("%s\n", res);
	initialize_data(&data);
	// extract_pwd(&data);
	// handle_envp(&data);
	t_env* env = parse_environment(dup_env(envp));
	if (!env)
		printf("no env\n");
	minishell_loop(&data, env);
	return (0);
}
