/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 04:50:06 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/19 06:01:35 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void    print_commands_count(t_command_pipeline *pipeline)
{
    printf("Number of commands: %d\n", pipeline->number_of_commands);
}

void    print_commands(t_command_pipeline *pipeline)
{
    // print commands
    int z = 0;
    printf("Commands:\n");
    while (z < pipeline->number_of_commands)
    {
        printf("command %d is: %s\n",z + 1, pipeline->commands[z].command);
        z++;
    }
    // end print commands
}

void    print_args(t_command_pipeline *pipeline)
{
    printf("Arguments:\n");
    int z;
    int y;

    z = 0;
    y = 0;
    while (y < pipeline->number_of_commands)
    {
        z = 0;
        while (pipeline->commands[y].args[z])
        {
            printf("Argument %d of command %s: %s\n",
                z+1, pipeline->commands[y].command, pipeline->commands[y].args[z]);
            z++;
        }
        y++;
    }
}

void    print_input_files(t_command_pipeline *pipeline)
{
    int x;

    x = 0;
    while (x < pipeline->number_of_commands)
    {
        printf("input file for command %s: %s\n", pipeline->commands[x].command, pipeline->commands[x].input_file);
        x++;
    }
}

void    print_output_files(t_command_pipeline *pipeline)
{
    int x;

    x = 0;
    while (x < pipeline->number_of_commands)
    {
        printf("output file for command %s: %s\n", pipeline->commands[x].command, pipeline->commands[x].output_file);
        x++;
    }
}


void printer(t_command_pipeline *pipeline)
{
    print_commands_count(pipeline);
    print_commands(pipeline);
    print_args(pipeline);
    print_input_files(pipeline);
    print_output_files(pipeline);
}