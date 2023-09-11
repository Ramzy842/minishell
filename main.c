/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/08 19:52:22 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void    minishell_loop(char **envp)
{
    char    *input = NULL;
    char    **tokens = NULL;
    char    **args = NULL;
    char    *command = NULL;
    char    *working_dir = NULL;

    while (1)
    {
        working_dir = print_current_dir();
        printf("\x1b[32mMinishell:\x1b[36m%s$ \x1b[0m", working_dir);
        input = readline("");
        if (!input)
            break ;
        if (ft_strlen(input) == 0)
        {
            printf("\n");
            free(input);
        }
        else 
        {
            // Add input to history
            add_history(input);

            // Parse and execute the command
            // Implement parsing and execution logic here

            tokens = ft_split(input, ' ');
            command = tokens[0];
            args = &tokens[1];
            if (ft_strcmp(command, "cd") == 0)
                handle_cd(args);
            else if (ft_strcmp(command, "pwd") == 0)
                printf("%s\n", working_dir);
            else if (ft_strcmp(command, "echo") == 0)
                // handle_echo(args);
                handle_echo(args, input);
            else if (ft_strcmp(command, "export") == 0)
            {
                printf("exporting...\n");
            }
            else if (ft_strcmp(command, "unset") == 0)
            {
                printf("unsetting...\n");
            }
            else if (ft_strcmp(command, "env") == 0)
                handle_env(envp, args);
            else if (ft_strcmp(command, "exit") == 0)
            {
                printf("exiting...\n");
                free(input);
                break ;
            }
            else if (ft_strcmp(command, "$") == 0)
            {
                printf("%s: command not found\n", command);
            }
            else if (ft_strcmp(command, ".") == 0)
            {
                printf("Minishell: %s: filename argument required\n.: usage: . filename [arguments]\n", command);
            }
            else
                printf("Command '%s' not found\n", command);
            free(input);
        }
    }
}



int main(int argc, char **argv, char **envp) 
{
    if (argc != 1 || argv[1])
    {
        printf("Minishell does not accept arguments.\n");
        return (1);
    }
    minishell_loop(envp);
    return (0);
}
