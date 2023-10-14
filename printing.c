/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:50:06 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:13:49 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


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

void print_char_array(char** array, int size)
{
	for (int i = 0; i < size; i++)
    	printf("%s\n", array[i]);
}

void	print_cmd_lst(t_commands* cmd)
{
	while (cmd)
	{
		int i = 0;
		printf("argv: ");
		while (cmd->command_args[i])
		{
			printf("%s", cmd->command_args[i]);
			if (cmd->command_args[i + 1])
				printf(", ");
			i++;
		}
		printf("\n");
		printf("input_redir: %i | output_redir: %i\n", cmd->i_redir, cmd->o_redir);
		printf("input_file: %s  | output_file: %s\n", cmd->input_filename, cmd->output_filename);
		printf("\n");
		cmd = cmd->next;
	}
}