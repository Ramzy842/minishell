/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:24:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/01 11:31:15 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	parser(t_data *data)
{
	int				pipes_count;
	t_simple_cmds	*node;
	t_parser_data	parser_data;

	data->simple_cmds = NULL;
	pipes_count = get_pipes_count(data->lexer_list, data);
	if (data->lexer_list->token == PIPE)
		return (parser_double_token_error(data, data->lexer_list,
				data->lexer_list->token));
	// while (data->lexer_list)
	// {
	// 	if (data->lexer_list && data->lexer_list->token == PIPE)
	// 		ft_lexerdelone(&data->lexer_list, data->lexer_list->index);
	// 	if (handle_pipe_errors(data, data->lexer_list->token))
	// 		return (EXIT_FAILURE);
	// 	parser_data = init_parser_data(data->lexer_list, data);
	// 	node = initialize_cmd(&parser_data);
	// 	if (!node)
	// 		parser_error(0, data, parser_data.lexer_list);
	// 	if (!data->simple_cmds)
	// 		data->simple_cmds = node;
	// 	else
	// 		ft_simple_cmdsadd_back(&data->simple_cmds, node);
	// 	data->lexer_list = parser_data.lexer_list;
	// }
	return (EXIT_SUCCESS);
}
