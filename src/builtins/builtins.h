/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:52:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/22 22:09:15 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../parsing/parsing.h"
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*find_path_ret(char *str, t_data *data);
void	change_path(t_data *data);
int		specific_path(t_data *data, char *str);
void	add_path_to_env(t_data *data);
int		buit_cd(t_commands *cmd);
void	print_lines(int i, char **str, int out);
int		bult_echo(t_commands *cmd);
int		ft_pwd(void);
int		ft_errors(char *cmd, char *error);
int		bult_exit(char **args);
int		bult_unset(t_commands *cmd, t_env *env);
int		bult_export(t_commands *cmd, t_env *env);
int		ft_setenv(char *var, char *value, t_env *env);
t_env	*ft_lstnew(void *key);
int		bult_env(t_env *env);
int		check_var(char *var);
void	set_env_variable(char *var, char *value, t_env *env);
int		ft_print_export(t_env *env);
t_env	*create_and_insert_env_variable(char *var, char *value, t_env *env,
			t_env *prev);
int		check_the_number(char *str);
int		ft_search_set(char *new, char *var, t_env *tmp_env);
void	ft_lstadd_back(t_env **env, t_env *new);

#endif