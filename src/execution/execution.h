/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 13:07:59 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h" 
// #include "../../minishell.h"

#ifndef EXECUTION_H
#define EXECUTION_H
//void minishell_execute(t_commands* cmd, t_env* env , t_data *data);
// int		minishell_execute(t_commands* cmd, t_env* env ,t_data *data);
char	*get_cmd_abs_path(t_env* env, char* cmd);
void	free_tools(t_data *data);
int		handle_builtin_commands(t_data *data, t_commands *cmd);
int		ft_redir(t_commands *cmd);
// void    exe_builtins(t_data *data, t_commands *cmd);
#endif