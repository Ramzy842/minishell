/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 23:04:39 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h" 

#ifndef EXECUTION_H
#define EXECUTION_H
int minishell_execute(t_commands *cmd, t_env *env, t_data *data);
char*   get_cmd_abs_path(t_env* env, char* cmd);
int check_is_builting(  t_commands *cmd);
int	exec_builtin_commands(t_commands *cmd, t_env *env);
int ft_redir(t_commands *cmd);
int	ft_setenv(char *var, char *value, t_env *env );
#endif

