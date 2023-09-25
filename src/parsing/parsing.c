/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/25 09:47:26 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing.h"

int is_between_matching_quotes(char *str)
{
	
    int x = 0;
    int inside_single_quotes = 0;
    int inside_double_quotes = 0;

    while (str[x] != '\0')
	{
        if (str[x] == '\'')
		{
            if (inside_double_quotes == 0)
                inside_single_quotes = !inside_single_quotes;
        }
		else if (str[x] == '"')
		{
            if (inside_single_quotes == 0)
                inside_double_quotes = !inside_double_quotes;
			else
                return 0; // Double quotes inside single quotes, return 0 (not matching)
        }
        x++;
    }
	if (inside_single_quotes % 2 == 0 && inside_double_quotes % 2 == 0)
		return (1);
	return (0);
    // return (insideSingleQuotes % 2 == 0 && insideDoubleQuotes % 2 == 0) ? 1 : 0;
}

void    default_input_parsing(char **tokens, t_command_pipeline *pipeline, int *x)
{
    char **full_command = ft_split_spaces(remove_beg_end(tokens[*x]));
	full_command = tok_w_no_quotes(full_command);
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
        pipeline->commands[x].input_file = NULL;
        pipeline->commands[x].output_file = NULL;
		pipeline->commands[x].vars = NULL;
        x++;
    }
}

int		args_are_matching(char **args)
{
	int	x;

	x = 0;
	while (args[x])
	{
		//printf("hada arg ghaytchecka: %s\n", args[x]);
		if (args[x][0] == '"' || args[x][0] == '\'' ||
			args[x][ft_strlen(args[x]) - 1] == '"' || args[x][ft_strlen(args[x]) - 1] == '\'')
		{
			if (!is_between_matching_quotes(args[x]))
				//printf("(%s) is invalid\n", args[x]);
				return (0);
		}
		x++;
	}
	return (1);
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