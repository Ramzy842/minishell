/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:47:53 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 01:42:20 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static	char	*ft_getline_herdoc(char *heredoc, t_env *env, int status)
{
	char	*line;
	char	*temp;

	line = NULL;
	temp = NULL;
	if (!heredoc || g_signal == -2)
		return (NULL);
	while (1)
	{
		line = readline("< ");
		if (!line || !ft_strcmp(line, heredoc) || g_signal == -2)
		{
			if (line)
				free(line);
			break ;
		}
		temp = ft_strjoinget(temp, expand_variables(line, env, status));
		temp = ft_strjoinget(temp, "\n");
		if (line)
			free(line);
	}
	return (temp);
}

char	*ft_get_heredoc(char *heredoc, t_env *env, int status)
{
	char	*tmp;

	if (!heredoc)
		return (NULL); 
	tmp = ft_getline_herdoc(heredoc, env, status);
	return (tmp);
}

void	redirect_heredoc(t_commands *tmp, t_data *data, t_env *env, int status)
{
	(void)env;
	if (tmp->input_filename)
		free(tmp->input_filename);
	tmp->input_filename = ft_strdup(remove_quotes(data->lexer_list->next->str));
	tmp->i_redir = IO_HEREDOC;
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
	tmp->heredoc = ft_get_heredoc(tmp->input_filename, env, status);
}
