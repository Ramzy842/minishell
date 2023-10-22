/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:47:05 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/21 23:53:39 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h" 

#ifndef EXECUTION_H
#define EXECUTION_H
int minishell_execute(t_commands *cmd, t_env *env, t_data *data);
char*   get_cmd_abs_path(t_env* env, char* cmd);
int check_is_builting(  t_commands *cmd);
void	free_tools(t_data *data);
// int exec_builtin_commands( t_commands *cmd);
int	exec_builtin_commands(t_commands *cmd, t_env *env);
int	ft_redir(t_commands *cmd, int *pipefd, int tmp_fd);
char	*get_cmd_abs_path(t_env *env, char *cmd);
// void parent_proc(int pipefd[2], int tmp_fd, t_commands* cmd);
// int child_proc(t_commands* cmd, t_env* env, int tmp_fd, t_data* data);
//char	*is_cmd_exists(char **exe, t_env *env );
// void    exe_builtins(t_data *data, t_commands *cmd);
#endif

// int	ft_execute(t_cmd *cmd, t_list *envp)
// {
// 	char	**env;
// 	int		exit_status;

// 	exit_status = 0;
// 	if (ft_redaraction(cmd->redir_in.file, cmd->redir_in.type) == -1)
// 	{
// 		return (1);
// 	}
// 	if (ft_redaraction(cmd->redir_out.file, cmd->redir_out.type) == -1)
// 		return (1);
// 	if (cmd->args[0])
// 	{
// 		env = ft_lst_to_char(envp);
// 		exit_status = execve(cmd->args[0], cmd->args, env);
// 	}
// 	ft_error(cmd->args[0], strerror(errno));
// 	exit(exit_status);
// 	return (1);
// }
