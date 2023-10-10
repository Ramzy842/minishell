/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:50:06 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/09 15:55:27 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void print_pipes_count(t_data *data)
{
	printf("pipes present in the pipeline: %d\n", data->pipes);
}

void print_token_type(t_tokens token)
{
	if (token == 0)
		printf("token is a \x1b[36mWORD\x1b[0m\n");
	if (token == 1)
		printf("token is a \x1b[36mINPUT\x1b[0m\n");
	if (token == 2)
		printf("token is a \x1b[36mOUTPUT\x1b[0m\n");
	if (token == 3)
		printf("token is a \x1b[36mAPPEND\x1b[0m\n");
	if (token == 4)
		printf("token is a \x1b[36mHEREDOC\x1b[0m\n");
	if (token == 5)
		printf("token is a \x1b[36mPIPE\x1b[0m\n");
}

void	print_tokens_list(t_data *data)
{
	t_lexer *current = data->lexer_list;
	while(current)
	{
		printf("word is: \x1b[35m%s\x1b[0m and ", current->str);
		print_token_type(current->token);
		current = current->next;
	}
}

// void	print_commands(t_commands *command)
// {
// 	t_commands	*temp;
// 	int x = 0;
// 	//int idx = 0;
// 	temp = command;
// 	while (temp && temp->str)
// 	{
// 		//printf("command %d\n", x + 1);
// 		x = 0;
// 		printf("command %d\n", x + 1);
		
// 		printf("%s\n",temp->redirections->str);
// 		temp = temp->next;
// 		x++;
// 		printf("--------------------\n");
// 		//idx++;
// 	}
// 	printf("number of commands %d\n", x);
// }

// void printer(t_data *data, t_command *command)
// {
// 	(void) command;
// 	print_pipes_count(data);
// 	print_tokens_list(data);
// 	print_commands(command);
// 	//print_parser_data(parser_data);
// }

void print_lexer_list(t_lexer *list)
{
	t_lexer *current = list;
	printf("redir list: \n");
	while (current)
	{
		printf("str is (%s) and token is (%d)\n", current->str, current->token);
		current = current->next;
	} 
}

