/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:24:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/10 19:07:53 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// int	(*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd)
// {
// 	static void	*builtins[7][2] = {
// 	{"echo", mini_echo},
// 	{"cd", mini_cd},
// 	{"pwd", mini_pwd},
// 	{"export", mini_export},
// 	{"unset", mini_unset},
// 	{"env", mini_env},
// 	{"exit", mini_exit}
// 	};
// 	int			i;

// 	i = 0;
// 	while (i < 7)
// 	{
// 		if (str)
// 		{
// 			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
// 				return (builtins[i][1]);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

t_commands	*create_command_node(char **args, int num_of_redirections, t_lexer *redirections)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	if (!node)
		return (NULL);
	node->command_args = args;
	//node->builtin = builtin_arr(str[0]);
	// node->heredoc_del = NULL;
	node->number_of_redirections = num_of_redirections;
	node->redirections = redirections;
	node->next = NULL;
	return (node);
}

int	count_args(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		x;

	x = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->id >= 0)
			x++;
		tmp = tmp->next;
	}
	return (x);
}


void	free_lexer_nodes(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	handle_pipe_errors(t_data *data, t_tokens token)
{
	if (token == PIPE)
	{
		parser_double_token_error(data, data->lexer_list,
			data->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!data->lexer_list)
	{
		parser_error(0, data, data->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_parser_data initialize_parser(t_data *data)
{
	t_parser_data	parser_data;
	
	parser_data.data = data;
	parser_data.lexer_list = data->lexer_list;
	parser_data.number_of_redirections = 0;
	parser_data.redirections = NULL;
	return (parser_data);
}


// int	add_new_redirection(t_lexer *temp, t_parser_data *parser_data)
// {
// 	t_lexer	*node;
// 	int		id_1;
// 	int		id_2;

// 	node = create_lexer_node(ft_strdup(temp->next->str), temp->token);
// 	// test
// 	// printf("redirection str %s and token %d\n", temp->next->str, temp->token);
// 	// test
// 	if (!node)
// 		parser_error(1, parser_data->data, parser_data->lexer_list);
// 	append_node(&parser_data->redirections, node);
// 	id_1 = temp->id;
// 	id_2 = temp->next->id;
// 	remove_lexer_node(&parser_data->lexer_list, id_1);
// 	remove_lexer_node(&parser_data->lexer_list, id_2);
// 	parser_data->number_of_redirections++;
// 	return (0);
// }

int	add_new_redirection(t_lexer *temp, t_parser_data *parser_data)
{
	t_lexer	*node;
	int		id_1;
	int		id_2;

	node = create_lexer_node(ft_strdup(temp->next->str), temp->token);
	// test
	// printf("redirection str %s and token %d\n", temp->next->str, temp->token);
	// test
	if (!node)
		parser_error(1, parser_data->data, parser_data->lexer_list);
	append_node(&parser_data->redirections, node);
	id_1 = temp->id;
	id_2 = temp->next->id;
	remove_lexer_node(&parser_data->lexer_list, id_1);
	remove_lexer_node(&parser_data->lexer_list, id_2);
	parser_data->number_of_redirections++;
	return (0);
}

void	handle_redirections(t_parser_data *parser_data)
{
	t_lexer	*temp;
	temp = parser_data->lexer_list;
	while (temp && temp->token == 0)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return ;
	if (!temp->next)
		parser_error(0, parser_data->data, parser_data->lexer_list);
	if (temp->next->token)
		parser_double_token_error(parser_data->data,
			parser_data->lexer_list, temp->next->token);
	if ((temp->token >= INPUT && temp->token <= HEREDOC))
	{
		printf("added redirecton: %s, and token %d\n", temp->str, temp->token);
		add_new_redirection(temp, parser_data);
	}
	handle_redirections(parser_data);
}

void	add_command_node(t_commands **lst, t_commands *new)
{
	t_commands	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	// printf("tzadt\n");
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

int check_pipe_last(t_data *data)
{
	t_lexer *temp = data->lexer_list;
	while (temp->next)
		temp = temp->next;
	if (temp->token == PIPE || (temp->token >= INPUT && temp->token <= HEREDOC))
		return (1);
	return (0);
}

int count_commands(t_lexer *lexer_list)
{
	t_lexer *temp = lexer_list;
	int count = 0;
	while (temp)
	{
		if (temp->token == PIPE || !temp->next)
			count++;
		temp = temp->next;
	}
	return (count);
}


int count_redir(t_data *data, int x)
{
	int y = 0;
	t_data *temp = data;
	int redir_count = 0;
	while (temp->lexer_list && y < x)
	{
		if (temp->lexer_list->token != PIPE)
		{
			if (temp->lexer_list->token >= INPUT
				&& temp->lexer_list->token <= HEREDOC)
				redir_count++;
		}
		y++;
		temp->lexer_list = temp->lexer_list->next;
	}
	return (redir_count);
}


void print_2d_arr(char **args)
{
	int x = 0;
	while (args[x] != NULL)
	{
		printf("%s, ", args[x]);
		x++;
	}	
	printf("\n");
}

void init_redirs(t_lexer **list)
{
	t_lexer *temp;

	temp = *list;
	
	while (temp)
	{
		temp->str = NULL;
		temp->token = -1;
		temp = temp->next;	
	}
}

void extract_command(t_data **data, int x, int *command_id,int redirs)
{
	int y = 0;
	t_data *temp = *data;
	int tok_present = 0;
	int redir_count = 0;
	char *str = malloc(1);
	str[0] = '\0';
	printf("num redir %d\n", redirs);
	if (redirs > 0)
	{
		temp->commands->redirections = malloc(sizeof(t_lexer) * redirs);
		if (!temp->commands->redirections)
			return ;
	}
	init_redirs(&temp->commands->redirections);
	while (y < x)
	{
		if (temp->lexer_list->token != PIPE)
		{
			if (temp->lexer_list->token >= INPUT
				&& temp->lexer_list->token <= HEREDOC)
			{
				tok_present = 1;
				redir_count++;
				if (temp->lexer_list->next->str && temp->lexer_list->token)
				{
					add_node(temp->lexer_list->next->str,
					  	temp->lexer_list->token, &temp->commands->redirections);
					// printf("hh\n");
					// temp->commands->redirections = temp->commands->redirections->next;
				}
			}
			else
			{
				if (tok_present == 0)
				{
					str = ft_strjoin(str, temp->lexer_list->str);
					str = ft_strjoin(str, " ");
                }
			}
		}
		else
			(*command_id)++;
		y++;
		temp->lexer_list = temp->lexer_list->next;
	}
	char **args = ft_split(str, ' ');
	t_commands *new_cmd = create_command_node(args,
		redir_count, temp->commands->redirections);
	add_command_node(&temp->commands, new_cmd);
	printf("-----------------------------------------------------------\n");
}

int	launch_parser(t_data *data)
{
	if (check_pipe_last(data))
	{
		printf("a token is last\n");
		return (0);
	}
	int number_of_cmds = count_commands(data->lexer_list);
	data->commands = malloc(sizeof(t_commands) * number_of_cmds);
	update_pipes_count(data);
	int x = 1;
	int cmd_id = 1;
	printf("-------------------------------- PARSER -----------------------------------------\n");
	t_data temp_data;
	ft_memcpy(&temp_data, data, sizeof(t_data));
	t_lexer *temp_lexer_list = data->lexer_list;
	while (temp_lexer_list)
	{
		if (temp_lexer_list->token == PIPE || !temp_lexer_list->next)
		{	
			int redirs = count_redir(&temp_data, x);
			extract_command(&data, x, &cmd_id, redirs);
			x = 0;
		}
		x++;
		temp_lexer_list = temp_lexer_list->next;
	}
	print_lexer_list(data->commands->redirections);
	printf("commands: %d\n", number_of_cmds);
	return (EXIT_SUCCESS);
}


