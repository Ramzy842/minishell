/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/22 19:02:06 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;
int	minishell_loop(t_data *data, t_env *env);

int	reset_data(t_data *data, t_env *env)
{
	if (data->lexer_list)
		clear_lexer_nodes(&data->lexer_list);
	if (data->commands)
		clear_command_nodes(&data->commands);
	if (data->shell_input)
		free(data->shell_input);
	initialize_data(data);
	data->reset = 1;
	minishell_loop(data, env);
	return (1);
}

// char	*show_current_path(char *working_dir)
// {
// 	working_dir = print_current_dir();
// 	working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
// 	working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
// 	return (working_dir);
// }

int	ft_save_stdin_stdout(int *save_stdin, int *save_stdout)
{
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	return (1);
}

void ft_reset_stdin_stdout(int *save_stdin, int *save_stdout)
{
	dup2(*save_stdin, STDIN_FILENO);
	dup2(*save_stdout, STDOUT_FILENO);
	close(*save_stdin);
	close(*save_stdout);
}

t_commands	*gen_cmd_lst(t_data *data, t_env *env)
{
	t_commands	*head;
	t_commands	*tmp;
	int			x;
	int			fd[2];

	head = gen_cmd_node();
	tmp = head;
	x = 0;
	ft_save_stdin_stdout(&fd[0], &fd[1]);
	g_signal = -1;
	while (data->lexer_list)
	{
		if (!tmp->command_args)
		{
			tmp->command_args = malloc(sizeof(char *) * 2);
			ft_memset(tmp->command_args, 0, sizeof(char *) * 2);
		}
		while (data->lexer_list && !is_metachar(data->lexer_list->str))
			handle_args(tmp, &x, data, env);
		while (data->lexer_list && is_metachar(data->lexer_list->str))
		{
			if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "|"))
			{
				tmp->next = gen_cmd_node();
				x = 0;
				data->lexer_list = data->lexer_list->next;
				tmp = tmp->next;
				continue ;
			}
			if (!handle_redirections(data, tmp, env))
				return (NULL);
		}
	}
	if (g_signal == -1)
	{
		g_signal = 0;
	}
	ft_save_stdin_stdout(&fd[0], &fd[1]);
	return (head);
}

static char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		x;

	x = 0;
	res = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[x])
	{
		res[x] = s1[x];
		x++;
	}
	res[x] = c;
	free(s1);
	return (res);
}

char	*remove_quotes(char *cmd)
{
	int		x;
	int		dq;
	int		sq;
	char	*res;

	x = 0;
	dq = 0;
	sq = 0;
	res = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	while (cmd[x])
	{
		if (cmd[x] == '\'' && !dq)
			sq = !sq;
		else if (cmd[x] == '\"' && !sq)
			dq = !dq;
		else
			res = ft_strjoin_char(res, cmd[x]);
		x++;
	}
	return (res);
}

int	syntaxer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (!(tmp->token >= INPUT && tmp->token <= PIPE)
		&& get_list_length((t_lexer*)lexer) > 1
		&& ((tmp->next->token >= INPUT && tmp->next->token <= PIPE))
		&& !tmp->next->next)
		return (0);
	if ((tmp->token == PIPE)
		&& get_list_length((t_lexer*)lexer) > 1
		&& (!(tmp->next->token >= INPUT && tmp->next->token <= PIPE)))
		return (0);
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

int	minishell_loop(t_data *data, t_env *env)
{
	char	*temp;

	temp = NULL;
	data->commands = NULL;
	data->lexer_list = NULL;
	data->shell_input = readline("Minishell-> ");
	if (!data->shell_input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	temp = ft_strtrim(data->shell_input, " ");
	free(data->shell_input);
	data->shell_input = ft_strdup(temp);
	free(temp);
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
	if (!tokens_reader(data))
		return (ft_error(1, data, env));
	if (!syntaxer(data->lexer_list))
	{
		ft_putstr_fd("Syntax error\n", STDERR_FILENO);
		reset_data(data, env);
	}
	if (data->lexer_list)
	{
		data->commands = gen_cmd_lst(data, env);
		if (!data->commands)
			reset_data(data, env);
		else
		{
			minishell_execute(data->commands, env, data);
			reset_data(data, env);
		}
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



// void	ft_handler(int sig)
// {
// 	(void)sig;
// 	if (g_signal > 0)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 	}
// 	else
// 	{
// 		if (g_signal == -1)
// 		{
// 			close(STDIN_FILENO);
// 			g_signal = -2;
// 		}
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_env	*env;

	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments.\n");
		exit(0);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	g_signal = 0;
	initialize_data(&data);
	env = parse_environment(dup_env(envp));
	if (!env)
		return (1);
	minishell_loop(&data, env);
	return (0);
}
