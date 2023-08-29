/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/08/29 17:15:29 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_double_quotes(char *str)
{
    int x;
    int idx;
    char *ptr;
    
    x = 0;
    idx = 0;
    ptr = malloc(ft_strlen(str) * sizeof(char) + 1);
    while (str[x])
    {
        if (str[x] != '\"')
        {
            ptr[idx] = str[x];
            idx++;
        }
        x++;
    }
    ptr[idx] = '\0';
    return (ptr);
}

void    minishell_loop()
{
    char    *input = NULL;
    char    **tokens = NULL;
    char    **args = NULL;
    char    *command = NULL;
    char    *working_dir = NULL;

    while (1)
    {
        working_dir = print_current_dir();
        printf("Minishell:%s$ ", working_dir);
        input = readline("");
        if (!input)
            break ;
        if (ft_strlen(input) == 0)
            printf("\n");
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
            {
                if (args[0] == NULL )
                    printf("\n");
                else
                {
                    int x = 0;
                    char *temp = remove_double_quotes(join_args(args));
                    args = ft_split(temp, ' ');
                    if (ft_strcmp(args[0], "-n") == 0)
                    {
                        x = 1;
                        while (args[x + 1])
                        {
                            printf("%s ", args[x]);
                            x++;
                        }
                        printf("%s", args[x]);
                    }
                    else
                    {
                        while (args[x + 1])
                        {
                            printf("%s ", args[x]);
                            x++;
                        }
                        printf("%s\n", args[x]);
                    }
                }
            }
            else if (ft_strcmp(command, "export") == 0)
            {
                printf("exporting...\n");
            }
            else if (ft_strcmp(command, "unset") == 0)
            {
                printf("unsetting...\n");
            }
            else if (ft_strcmp(command, "env") == 0)
            {
                printf("environment variable...\n");
            }
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



int main(int argc, char **argv) 
{
    if (argc != 1 || argv[1])
    {
        printf("Minishell does not accept arguments.\n");
        return (1);
    }
    minishell_loop();
    return (0);
}
