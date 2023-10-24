/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:30:38 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

int		minishell_execute(t_commands *cmd, t_env *env, t_data *data);
char	*get_cmd_abs_path(t_env *env, char *cmd);
int		check_is_builting(t_commands *cmd);
int		exec_builtin_commands(t_commands *cmd, t_env *env);
int		ft_redir(t_commands *cmd, int *pipefd, int tmp_fd);
char	*get_cmd_abs_path(t_env *env, char *cmd);
void	ft_handler(int sig);
int		exec_builtin_commands(t_commands *cmd, t_env *env);
int		check_is_builting(t_commands *cmd);
int		check_if_its_a_directory(char *path);
int		check_and_handle_command(t_commands *cmd, t_env *env);
char	*check_abs_path(char *cmd);
int		ft_status(int status);
int		ft_exec_one(t_commands *cmd, t_env *env);
int		ft_child(t_commands *cmd, t_env *env, int *pipefd, int tmp_fd);
int		ft_pipe(t_commands *cmd, t_env *env);
int		ft_wait_for_child(int pid);

#endif
