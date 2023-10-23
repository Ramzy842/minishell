/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 00:50:52 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

int		minishell_execute(t_commands *cmd, t_env *env, t_data *data);
char	*get_cmd_abs_path(t_env *env, char *cmd);
int		check_is_builting(t_commands *cmd);
void	free_tools(t_data *data);
// int exec_builtin_commands( t_commands *cmd);
int		exec_builtin_commands(t_commands *cmd, t_env *env);
int		ft_redir(t_commands *cmd, int *pipefd, int tmp_fd);
char	*get_cmd_abs_path(t_env *env, char *cmd);
// void	ft_handler(int sig);
int		exec_builtin_commands(t_commands *cmd, t_env *env);
int		check_is_builting(t_commands *cmd);
// void parent_proc(int pipefd[2], int tmp_fd, t_commands* cmd);
// int child_proc(t_commands* cmd, t_env* env, int tmp_fd, t_data* data);
//char	*is_cmd_exists(char **exe, t_env *env );
// void    exe_builtins(t_data *data, t_commands *cmd);
#endif
