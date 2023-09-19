/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:57:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/19 05:59:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void    redirect_output(char **tokens, t_command_pipeline *pipeline, int *x)
{
    char **full_command = ft_split(tokens[*x], '>');
    char **first_part = ft_split_spaces(remove_beg_end(full_command[0]));
    pipeline->commands[*x].command = first_part[0];
    pipeline->commands[*x].args = malloc(sizeof(char *) * ft_strlen_2d(first_part));
    int y = 1;
    int idx = 0;
    while (first_part[y] != NULL)
    {
        pipeline->commands[*x].args[idx] = first_part[y];
        y++;
        idx++;
    }
    pipeline->commands[*x].args[idx] = NULL;
    // end filling args of single command
    pipeline->commands[*x].output_file = malloc(sizeof(char) * ft_strlen(full_command[1]));
    if (!pipeline->commands[*x].output_file)
        return ;
    pipeline->commands[*x].output_file = full_command[1];
    pipeline->commands[*x].pipe_to = *x + 1;
}