/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:57:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/28 00:32:13 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	assign_output_files(char **full_command,  t_output_files *files)
{
	int	x;
	int	idx;
	
	x = 1;
	idx = 0;
	printf("print full command | output files\n");
	print_full_command(full_command);
	while (x <= ft_strlen_2d(full_command))
	{
		files[idx].file = full_command[x];
		files[idx].order = x;
		x++;
		idx++;
	}
	printf("-------------------------------------------------------------\n");
}

void    redirect_output(char **tokens, t_command_pipeline *pipeline, int *x)
{
    char **full_command = ft_split(tokens[*x], '>');
    char **first_part = ft_split_spaces(remove_beg_end(full_command[0]));
	//first_part = tok_w_no_quotes(first_part);
    pipeline->commands[*x].command = first_part[0];
    pipeline->commands[*x].args = malloc(sizeof(char *) * ft_strlen_2d(first_part));
	pipeline->commands[*x].output_files = malloc(sizeof(t_output_files) * ft_strlen_2d(full_command));
	pipeline->commands[*x].output_files[ft_strlen_2d(full_command)].file = NULL;
    if (!pipeline->commands[*x].output_files)
        return ;
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
	assign_output_files(full_command, pipeline->commands[*x].output_files);
    pipeline->commands[*x].pipe_to = *x + 1;
}