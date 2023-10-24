/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:18:12 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	initialize_data(t_data *data)
{
	data->shell_input = NULL;
	data->x = 0;
	data->commands = NULL;
	data->envp = NULL;
	data->lexer_list = NULL;
	data->reset = 0;
	data->pid = NULL;
	data->heredoc = 0;
	return (1);
}

int	syntaxer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (!(tmp->token >= INPUT && tmp->token <= PIPE)
		&& get_list_length((t_lexer*)lexer) > 1
		&& ((tmp->next->token >= INPUT && tmp->next->token <= PIPE))
		&& !tmp->next->next)
		return (0);
	if ((tmp->token == PIPE)
		&& get_list_length((t_lexer*)lexer) > 1
		&& (!(tmp->next->token >= INPUT && tmp->next->token <= PIPE)))
		return (0);
	if ((tmp->token >= INPUT && tmp->token <= PIPE)
		&& get_list_length((t_lexer*)lexer) == 1)
		return (0);
	while (tmp)
	{
		if ((tmp->token >= INPUT && tmp->token <= PIPE) && !tmp->next)
			return (0);
		if (tmp->token >= INPUT && tmp->token <= PIPE
			&& tmp->next->token >= INPUT && tmp->next->token <= PIPE)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		x;

	if (!s1)
		return (NULL);
	x = 0;
	res = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[x])
	{
		res[x] = s1[x];
		x++;
	}
	res[x] = c;
	return (res);
}

char	*remove_quotes(char *cmd)
{
	int		x;
	int		dq;
	int		sq;
	char	*res;

	x = 0;
	dq = 0;
	sq = 0;
	res = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	while (cmd[x])
	{
		if (cmd[x] == '\'' && !dq)
			sq = !sq;
		else if (cmd[x] == '\"' && !sq)
			dq = !dq;
		else
			res = ft_strjoin_char(res, cmd[x]);
		x++;
	}
	return (res);
}

int	init_starting_props(char *temp, t_data *data)
{
	data->commands = NULL;
	data->lexer_list = NULL;
	data->shell_input = readline("Minishell-> ");
	if (!data->shell_input)
		return (EXIT_SUCCESS);
	temp = ft_strtrim(data->shell_input, " \n\t");
	free(data->shell_input);
	data->shell_input = ft_strdup(temp);
	free(temp);
	return (1);
}
