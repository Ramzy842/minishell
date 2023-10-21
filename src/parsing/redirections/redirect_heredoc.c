/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr <yel-hadr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:47:53 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/21 02:33:45 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


  static char	*ft_getline_herdoc(char *heredoc) /////// added this function 
{
	char *line;
	char *temp = NULL; 
	while(1)
	{
		line  =readline("< ");
		if(!line || !ft_strcmp(line, heredoc)) // || signals
			{
				free(line);
				break;
			}
		// expand line (expansion function used in expansion parsing)
		temp = ft_strjoinget(temp , line);
		temp =  ft_strjoinget(temp, "\n");
			if(line)
				free(line);
	}
		// the heredoc work perfectly buut theproblem occurs cat<< ss 
		
	return temp;
}

char	*ft_get_heredoc(char *heredoc) /////// added
{
	char	*tmp;
 	if (!heredoc) //sig
		return (NULL);
		//check expand 
	tmp = ft_getline_herdoc(heredoc);
	return (tmp);
}

void	redirect_heredoc(t_commands* tmp, t_data *data)
{
	if (tmp->input_filename)
		free(tmp->input_filename);
	tmp->input_filename = ft_strdup(data->lexer_list->next->str);
	tmp->i_redir = IO_HEREDOC;
	data->lexer_list = data->lexer_list->next;
	if (data->lexer_list)
		data->lexer_list = data->lexer_list->next;
	tmp->heredoc = ft_get_heredoc(tmp->input_filename);/////// added this line
		
}