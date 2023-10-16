/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:18:05 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/15 13:32:57 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


// void	ft_simple_cmdsclear(t_commands **list)
// {
// 	t_commands	*tmp;
// 	t_lexer			*redirections_tmp;

// 	if (!*list)
// 		return ;
// 	while (*list)
// 	{
// 		tmp = (*list)->next;
// 		redirections_tmp = (*list)->;
// 		ft_lexerclear(&redirections_tmp);
// 		if ((*list)->str)
// 			free_arr((*list)->str);
// 		if ((*list)->hd_file_name)
// 			free((*list)->hd_file_name);
// 		free(*list);
// 		*list = tmp;
// 	}
// 	*list = NULL;
// }


void	free_tools(t_data *data)
{

	if (data->pipes)
		free(data->pid);
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	determine_exit_code(char **str)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (is_str_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	free_arr(str);
	exit(exit_code);
}

int	bult_exit(t_data *data, t_commands *cmd)
{
	char	**str;
	(void) *data;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->command_args[1] && cmd->command_args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = ft_arrdup(cmd->command_args);
	determine_exit_code(str);
	return (EXIT_SUCCESS);
}
