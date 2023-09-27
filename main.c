/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/27 21:49:45 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./src/parsing/parsing.h"

void    minishell_loop(char **envp, t_command_pipeline *pipeline)
{
    char    *input = NULL;
    char    *history_input = NULL;
    char    **tokens = NULL;
    char    *working_dir = NULL;
    int     x;

    (void) envp;
    x = 0;
    while (1)
    {
        working_dir = print_current_dir();
		working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
		working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
        input = readline(working_dir);
        //printf("\x1b[32mMinishell:\x1b[36m%s$ \x1b[0m", working_dir);
        history_input = input;
        input = remove_beg_end(input);
        if (!input)
            break ;
        if (ft_strlen(input) == 0)
        {
            //printf("\n");
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
            while (tokens[x])
                x++;
            pipeline->number_of_commands = x;
            pipeline->commands = malloc(sizeof(t_command) * pipeline->number_of_commands);
            initialize_commands(pipeline);
			if (!tokens_quotes_validation(tokens))
				printf("Error: quotes not matching\n");
			else
			{
				x = 0;
				while (x < pipeline->number_of_commands)
				{
				    if (ft_strnstr(tokens[x], "<", ft_strlen(tokens[x])))
				        redirect_input(tokens, pipeline, &x);
				    if (ft_strnstr(tokens[x], ">", ft_strlen(tokens[x])))
				        redirect_output(tokens, pipeline, &x);
				    else
				        default_input_parsing(tokens, pipeline, &x);
				    x++;
				}
            	// prints commands info
            	printer(pipeline, ft_split_spaces(tokens[0]));
				expander(pipeline, NULL);
			}
            // ending new struct code

            // tokens = ft_split(input, ' ');
            // command = tokens[0];
            // args = &tokens[1];
            // if (ft_strcmp(pipeline->commands[0].command, "cd") == 0)
            //    handle_cd(pipeline->commands[0].args);
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
    }
}

int main(int argc, char **argv, char **envp) 
{
    t_command_pipeline  pipeline;

    if (argc != 1 || argv[1])
    {
        printf("Minishell does not accept arguments.\n");
        return (1);
    }
    pipeline.number_of_commands = 0;
    pipeline.commands = NULL;
    minishell_loop(envp, &pipeline);
    return (0);
}
