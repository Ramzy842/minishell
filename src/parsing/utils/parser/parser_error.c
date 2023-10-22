/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:29:31 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/22 22:35:01 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

// int	parser_double_token_error(t_data *data, t_lexer *lexer_list,
// 	t_tokens token)
// {
// 	ft_putstr_fd("minishell: syntax error near unexpected token ",
// 		STDERR_FILENO);
// 	if (token == OUTPUT)
// 		ft_putstr_fd("'>'\n", STDERR_FILENO);
// 	else if (token == APPEND)
// 		ft_putstr_fd("'>>'\n", STDERR_FILENO);
// 	else if (token == INPUT)
// 		ft_putstr_fd("'<'\n", STDERR_FILENO);
// 	else if (token == HEREDOC)
// 		ft_putstr_fd("'<<'\n", STDERR_FILENO);
// 	else if (token == PIPE)
// 		ft_putstr_fd("'|'\n", STDERR_FILENO);
// 	else
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 	clear_lexer_nodes(&lexer_list);
// 	reset_data(data);
// 	return (EXIT_FAILURE);
// }

int	parser_double_token_error(t_data *data, t_lexer *lexer_list,
	t_tokens token)
{
	(void) data;
	(void) token;
	ft_putstr_fd("minishell: syntax error\n",
		STDERR_FILENO);
	clear_lexer_nodes(&lexer_list);
	return (EXIT_FAILURE);
}

int	ft_error(int error, t_data *data, t_env *env)
{
	(void)env;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	// reset_data(data, env,);
	(void) data;
	return (EXIT_FAILURE);
}

void	parser_error(int error, t_data *data, t_lexer *lexer_list)
{
	clear_lexer_nodes(&lexer_list);
	(void) data;
	(void) error;
}
