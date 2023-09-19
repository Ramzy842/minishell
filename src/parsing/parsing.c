/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/19 05:31:19 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing.h"

int is_between_quotes(char *str)
{
    if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
        return (1);
    return (0);
}

void    default_input_parsing(char **tokens, t_command_pipeline *pipeline, int *x)
{
    char **full_command = ft_split_spaces(remove_beg_end(tokens[*x]));
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
        x++;
    }
}