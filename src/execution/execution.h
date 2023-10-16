/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 05:26:59 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h" 

#ifndef EXECUTION_H
#define EXECUTION_H
//void minishell_execute(t_commands* cmd, t_env* env , t_data *data);
int    minishell_execute(t_commands* cmd, t_env* env ,t_data *data);
char*   get_cmd_abs_path(t_env* env, char* cmd);
void	free_tools(t_data *data);
int handle_builtin_commands(t_data *data, t_commands *cmd);
int ft_redir(t_commands *cmd);
// void    exe_builtins(t_data *data, t_commands *cmd);
#endif