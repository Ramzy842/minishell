/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/28 00:37:26 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing.h"

int is_between_matching_quotes(char *str)
{
	
    int length = strlen(str);
    if (length < 2)
        return 1;
    char start_quote = str[0];
    char end_quote = str[length - 1];
    if ((start_quote == '"' || start_quote == '\'') && start_quote == end_quote)
        return 1; // Word is enclosed in matching quotes
    return 0; // Word is not enclosed in matching quotes
}

void    default_input_parsing(char **tokens, t_command_pipeline *pipeline, int *x)
{
    char **full_command = ft_split_spaces(remove_beg_end(tokens[*x]));
	//full_command = tok_w_no_quotes(full_command);
    pipeline->commands[*x].command = full_command[0];
    pipeline->commands[*x].args = malloc(sizeof(char *) * ft_strlen_2d(full_command));

    int y = 1;
    int idx = 0;
    while (full_command[y] != NULL)
    {
        pipeline->commands[*x].args[idx] = full_command[y];
        y++;
        idx++;
    }
    pipeline->commands[*x].args[idx] = NULL;
    // end filling args of single command
    pipeline->commands[*x].pipe_to = *x + 1;
    // end default parsing
}

void    initialize_commands(t_command_pipeline *pipeline)
{
    int x;

    x = 0;
    pipeline->commands = malloc(sizeof(t_command) * pipeline->number_of_commands);
    while(x < pipeline->number_of_commands)
    {
        pipeline->commands[x].command = NULL;
        pipeline->commands[x].args = NULL;
        pipeline->commands[x].input_files = NULL;
        pipeline->commands[x].output_files = NULL;
		pipeline->commands[x].vars = NULL;
        x++;
    }
}

int		args_are_matching(char **args)
{
	int x = 0;

    while (args[x])
	{
        if (args[x][0] == '"' || args[x][0] == '\'')
		{
			// Check matching quotes only for words that start with a quote
            if (!is_between_matching_quotes(args[x]))
				return (0); // Word is not enclosed in matching quotes
        }
        x++;
    }
    return (1); // All words enclosed in matching quotes or not starting with quotes
}

int		tokens_quotes_validation(char **tokens)
{
	int	x;
	char **args = NULL;

	x = 0;
	while (tokens[x])
	{
		args = ft_split_spaces(tokens[x]);
		if (args_are_matching(args) == 0)
			return (0);
		x++;
	}
	return (1);
}