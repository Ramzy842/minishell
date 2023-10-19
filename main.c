/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/19 12:44:59 by rchahban         ###   ########.fr       */
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

t_commands* gen_cmd_lst(t_data* data, t_env *env)
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
			handle_args(tmp, &x, data, env);
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
			if (!handle_redirections(data, tmp, env))
			{
				return (NULL);
			}
		}
		// if (redir_err)
		// 	retru;
	}
	return (head);
}

// // remove_env (3la 9bl unset)
// // add_env (3la 9bl export)

// // char* get_cmd_abs_path(t_env* env, char* cmd)
// // {
// // 	t_env* path = get_env(env, "PATH");
// // 	if (!path)
// // 		return NULL;
// // 	char** path_spl = ft_split(path->value, ':');
// // 	if (!path_spl)
// // 		return NULL;
// // 	int i = 0;
// // 	while (path_spl[i])
// // 	{
// // 		char* tmp1 = ft_strjoin(path_spl[i], "/");
// // 		char* tmp2 = ft_strjoin(tmp1, cmd);
// // 		free(tmp1);
// // 		if (!access(tmp2, F_OK))
// // 			return tmp2;
// // 		i++;
// // 	}
// // 	return (NULL);
// // }

// // void minishell_execute(t_commands* cmd, t_env* env)
// // {
// // 	int child_pid;
// // 	int pipefd[2] = {-1, -1};
// // 	while (cmd)
// // 	{
// // 		if (!cmd->command_args[0])
// // 		{
// // 			cmd = cmd->next;
// // 			continue;
// // 		}
// // 		char* cmd_abs_path = get_cmd_abs_path(env, cmd->command_args[0]);
// // 		if (!cmd_abs_path && cmd->command_args[0])
// // 		{
// // 			printf("minishell: %s: command not found\n", cmd->command_args[0]);
// // 			cmd = cmd->next;
// // 			continue;
// // 		}
// // 		if (access(cmd_abs_path, X_OK) < 0 && cmd->command_args[0])
// // 		{
// // 			printf("minishell: %s: permission denied\n", cmd->command_args[0]);
// // 			cmd = cmd->next;
// // 			continue;
// // 		}
// // 		// we have a pipe
// // 		if (cmd->next)
// // 		{
// // 			pipe(pipefd);
// // 			cmd->out = pipefd[1];
// // 			cmd->next->in = pipefd[0];
// // 		}
// // 		// check for redirections
// // 		if (cmd->i_redir == IO_INPUT)
// // 		{
// // 			int fd = open(cmd->input_filename, O_RDONLY);
// // 			cmd->in = fd;
// // 		}
// // 		if (cmd->o_redir == IO_OUTPUT)
// // 		{
// // 			// its not necessary to pass O_CREAT to open since the parser should have created the file
// // 			int fd = open(cmd->output_filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
// // 			close(pipefd[1]);
// // 			cmd->out = fd;
// // 		}
// // 		if (cmd->o_redir == IO_APPEND)
// // 		{
// // 			int fd = open(cmd->output_filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
// // 			cmd->out = fd;
// // 		}
// // 		child_pid = fork();
// // 		if (!child_pid)
// // 		{
// // 			if (cmd->out != 1)
// // 			{
// // 				dup2(cmd->out, 1);
// // 				// 1 is now pointing at cmd->out, cmd->out is not needed anymore
// // 				close(cmd->out);
// // 			}
// // 			if (cmd->in != 0)
// // 			{
// // 				dup2(cmd->in, 0);
// // 				// same thing above, cmd->in is not needed anymore
// // 				close(cmd->in);
// // 			}
// // 			execve(cmd_abs_path, cmd->command_args, convert_env_to_arr(env));
// // 		}
// // 		if (cmd->out != 1)
// // 			close(cmd->out);
// // 		if (cmd->in != 0)
// // 			close(cmd->in);
// // 		cmd = cmd->next;
// // 	}
// // 	waitpid(child_pid, NULL, 0);
// // }

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

// // int	main(void)
// // {
// // 	char	*cmd;
// // 	char	*res;
// //
// // 	cmd = ft_strdup("echo \"hello world\"");
// // 	res = remove_quotes(cmd);
// // 	printf("%s\n", res);
// // 	return (0);
// // }

int syntaxer(t_lexer *lexer)
{
	t_lexer *tmp = lexer;
	if ((tmp->token == PIPE)
		&& get_list_length((t_lexer*)lexer) > 1 && (!(tmp->next->token >= INPUT && tmp->next->token <= PIPE)) )
		return (0);
	if ((tmp->token >= INPUT && tmp->token <= PIPE)
		&& get_list_length((t_lexer*)lexer) == 1)
		return (0);
	while (tmp)
	{
		if (tmp->token >= INPUT && tmp->token <= PIPE
			&& tmp->next->token >= INPUT && tmp->next->token <= PIPE)
			{
				clear_lexer_nodes(&tmp);
				return (0);
			}
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
	data->shell_input = readline("Minishell-> ");
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
		// data->lexer_list = expand_lexer(data->lexer_list, env); // working but I wanna try expanding commands list so i can ignore heredoc expansion
		// quotes_remover(data->lexer_list);
		data->commands = gen_cmd_lst(data, env);
		
		if (!data->commands)
			reset_data(data, env);
		else 
		{
			// print_cmd_lst(data->commands);
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
	initialize_data(&data);
	t_env* env = parse_environment(dup_env(envp));
	if (!env)
		return (0);
	minishell_loop(&data, env);
	free_env_list(env);
	free_arr(data.envp);
	free_arr(data.envp_arr);
	return (0);
}
