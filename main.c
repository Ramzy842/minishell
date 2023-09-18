/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/19 00:43:11 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen_2d(char **tab)
{
    int x = 0;
    while (tab[x])
        x++;
    return (x);
}

void    minishell_loop(char **envp, t_command_pipeline *pipeline)
{
    char    *input = NULL;
    char    *history_input = NULL;
    char    **tokens = NULL;
    char    *working_dir = NULL;
    (void) envp;
    while (1)
    {
        working_dir = print_current_dir();
        printf("\x1b[32mMinishell:\x1b[36m%s$ \x1b[0m", working_dir);
        input = readline("");
        history_input = input;
        input = remove_beg_end(input);
        if (!input)
            break ;
        if (ft_strlen(input) == 0)
        {
            printf("\n");
            free(input);
        }
        else if (input[ft_strlen(input) - 1] == '|')
        {
            printf("error pipe is last\n");
            free(input);
        }
        else 
        {
            // Add input to history
            add_history(history_input);

            // beginning new struct code
            tokens = ft_split(input, '|');
            // count num of commands
            int x = 0;
            while (tokens[x])
                x++;
            pipeline->number_of_commands = x;
            pipeline->commands = malloc(sizeof(t_command) * pipeline->number_of_commands);
            // end count num of commands
            //printf("num of commands is %d\n", pipeline->number_of_commands);
            x = 0;
            while (x < pipeline->number_of_commands)
            {
                if (ft_strnstr(tokens[x], "<", ft_strlen(tokens[x])))
                {
                    char **full_command = ft_split(tokens[x], '<');
                    char **first_part = ft_split_spaces(remove_beg_end(full_command[0]));
                    pipeline->commands[x].command = first_part[0];
                    pipeline->commands[x].args = malloc(sizeof(char *) * ft_strlen_2d(first_part));

                    int y = 1;
                    int idx = 0;
                    while (first_part[y] != NULL)
                    {
                        pipeline->commands[x].args[idx] = first_part[y];
                        y++;
                        idx++;
                    }
                    pipeline->commands[x].args[idx] = NULL;
                    // end filling args of single command
                    pipeline->commands[x].input_file = full_command[x + 1];
                    pipeline->commands[x].pipe_to = x + 1;
                }
                else if (ft_strnstr(tokens[x], ">", ft_strlen(tokens[x])))
                {
                    char **full_command = ft_split(tokens[x], '>');
                    char **first_part = ft_split_spaces(remove_beg_end(full_command[0]));
                    pipeline->commands[x].command = first_part[0];
                    pipeline->commands[x].args = malloc(sizeof(char *) * ft_strlen_2d(first_part));

                    int y = 1;
                    int idx = 0;
                    while (first_part[y] != NULL)
                    {
                        pipeline->commands[x].args[idx] = first_part[y];
                        y++;
                        idx++;
                    }
                    pipeline->commands[x].args[idx] = NULL;
                    // end filling args of single command
                    pipeline->commands[x].output_file = full_command[x + 1];
                    pipeline->commands[x].pipe_to = x + 1;
                }
                else
                {
                    // default parsing
                    char **full_command = ft_split_spaces(remove_beg_end(tokens[x]));
                    pipeline->commands[x].command = full_command[0];
                    pipeline->commands[x].args = malloc(sizeof(char *) * ft_strlen_2d(full_command));
                    
                    int y = 1;
                    int idx = 0;
                    while (full_command[y] != NULL)
                    {
                        pipeline->commands[x].args[idx] = full_command[y];
                        y++;
                        idx++;
                    }
                    pipeline->commands[x].args[idx] = NULL;
                    // end filling args of single command
                    pipeline->commands[x].pipe_to = x + 1;
                    // end default parsing
                }
                x++;
            }

            // ending new struct code

            // tokens = ft_split(input, ' ');
            // command = tokens[0];
            // args = &tokens[1];
            // if (ft_strcmp(command, "cd") == 0)
            //     handle_cd(args);
            // else if (ft_strcmp(command, "pwd") == 0)
            //     printf("%s\n", working_dir);
            // else if (ft_strcmp(command, "echo") == 0)
            //     // handle_echo(args);
            //     handle_echo(args, input);
            // else if (ft_strcmp(command, "export") == 0)
            // {
            //     printf("exporting...\n");
            // }
            // else if (ft_strcmp(command, "unset") == 0)
            // {
            //     printf("unsetting...\n");
            // }
            // else if (ft_strcmp(command, "env") == 0)
            //     handle_env(envp, args);
            // else if (ft_strcmp(command, "exit") == 0)
            // {
            //     printf("exiting...\n");
            //     free(input);
            //     break ;
            // }
            // else if (ft_strcmp(command, "$") == 0)
            // {
            //     printf("%s: command not found\n", command);
            // }
            // else if (ft_strcmp(command, ".") == 0)
            // {
            //     printf("Minishell: %s: filename argument required\n.: usage: . filename [arguments]\n", command);
            // }
            // else
            //     printf("Command '%s' not found\n", command);
            free(input);
        }
            printf("Number of commands: %d\n", pipeline->number_of_commands);
            // print commands
            int z = 0;
            printf("Commands:\n");
            while (z < pipeline->number_of_commands)
            {
                printf("command %d is: %s\n",z + 1, pipeline->commands[z].command);
                z++;
            }
            // end print commands
            printf("Arguments:\n");
            z = 0;
            int y = 0;
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
}



int main(int argc, char **argv, char **envp) 
{
    (void)envp;

    t_command_pipeline  pipeline;
    (void) pipeline;
    if (argc != 1 || argv[1])
    {
        printf("Minishell does not accept arguments.\n");
        return (1);
    }
    pipeline.number_of_commands = 0;
    pipeline.commands = NULL;
    minishell_loop(envp, &pipeline);
    // char *str = "hello \"world    \" i am groot hh";
    // char **split = ft_split_spaces(str);
    // int x = 0;
    // while(split[x])
    // {
    //     printf("%s|||", split[x]);
    //     x++;
    // }
    return (0);
}
