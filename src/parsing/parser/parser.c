/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:24:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/05 22:06:32 by rchahban         ###   ########.fr       */
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

t_command	*create_command_node(char **str,
	int num_of_redirections, t_lexer *redirections)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->str = str;
	//node->builtin = builtin_arr(str[0]);
	node->heredoc_file = NULL;
	node->number_of_redirections = num_of_redirections;
	node->redirections = redirections;
	node->next = NULL;
	node->prev = NULL;
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


int	add_new_redirection(t_lexer *temp, t_parser_data *parser_data)
{
	t_lexer	*node;
	int		id_1;
	int		id_2;

	node = create_lexer_node(ft_strdup(temp->next->str), temp->token);
	// test
	printf("redirection str %s and token %d\n", temp->next->str, temp->token);
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
		add_new_redirection(temp, parser_data);
	handle_redirections(parser_data);
}

t_command	*initialize_command(t_parser_data *parser_data)
{
	t_lexer	*temp;
	char	**str;
	int		x;
	int		arg_size;

	x = 0;
	handle_redirections(parser_data);
	arg_size = count_args(parser_data->lexer_list);
	str = malloc(arg_size * (sizeof(char *)));
	if (!str)
		parser_error(1, parser_data->data, parser_data->lexer_list);
	temp = parser_data->lexer_list;
	while (arg_size > 0)
	{
		if (temp->str)
		{
			str[++x] = ft_strdup(temp->str);
			remove_lexer_node(&parser_data->lexer_list, temp->id);
			temp = parser_data->lexer_list;
			//x++;
		}
		arg_size--;
	}
	return (create_command_node(str,
			parser_data->number_of_redirections, parser_data->redirections));
}

void	add_command_node(t_command **lst, t_command *new)
{
	t_command	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

int check_pipe_last(t_data *data)
{
	t_lexer *temp = data->lexer_list;
	while (temp->next)
		temp = temp->next;
	if (temp->token == PIPE)
		return (1);
	return (0);
}

int	launch_parser(t_data *data)
{
	t_command		*command;
	t_parser_data	parser_data;

	data->command = NULL;
	// begin pipe is last token in the pipeline handler (to be revisited)
	if (check_pipe_last(data))
	{
		printf("pipe is last\n");
		return (0);
	}
	// last pipe is last token in the pipeline handler (to be revisited)
	update_pipes_count(data);
	if (data->lexer_list->token == PIPE)
		return (parser_double_token_error(data, data->lexer_list,
				data->lexer_list->token));
	while (data->lexer_list)
	{
		if (data->lexer_list && data->lexer_list->token == PIPE)
		{
			printf("str is %s and token %d\n", data->lexer_list->str, data->lexer_list->token);
			remove_lexer_node(&data->lexer_list, data->lexer_list->id);
		}
		if (handle_pipe_errors(data, data->lexer_list->token))
			return (EXIT_FAILURE);
		parser_data = initialize_parser(data);
		command = initialize_command(&parser_data);
		if (!command)
			parser_error(0, data, parser_data.lexer_list);
		if (!data->command)
			data->command = command;
		else
			add_command_node(&data->command, command);
		data->lexer_list = parser_data.lexer_list;
	}
	return (EXIT_SUCCESS);
}
