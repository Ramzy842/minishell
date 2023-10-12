/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/12 18:48:47 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_between_matching_quotes(char *str)
{
	
    int length = ft_strlen(str);
    if (length < 2)
        return 1;
    char start_quote = str[0];
    char end_quote = str[length - 1];
    if ((start_quote == '"' || start_quote == '\'') && start_quote == end_quote)
        return 1; // Word is enclosed in matching quotes
    return 0; // Word is not enclosed in matching quotes
}


int    initialize_data(t_data *data)
{
	data->shell_input = NULL;
    data->commands = NULL;
	data->envp = NULL;
	data->lexer_list = NULL;
	data->reset = 0;
	data->pid = NULL;
	data->heredoc = 0;
	// g_global.stop_heredoc = 0;
	// g_global.command_mode = 0;
	// g_global.heredoc_mode = 0;
	//parse_envp(data);
	//init_signals();
	return (1);
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