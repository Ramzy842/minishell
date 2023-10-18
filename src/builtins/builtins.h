/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:52:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/17 14:39:57 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h" 
#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdlib.h>
#include <unistd.h>








size_t	equal_sign(char *str);
int	ft_isdigit(int c);
char	*delete_quotes_value(char *str);
int	check_valid_identifier(char c);
char	*delete_quotes(char *str, char c);
char	*find_path_ret(char *str, t_data *data);
void	change_path(t_data *data);
int	specific_path(t_data *data, char *str);
void	add_path_to_env(t_data *data);
int	buit_cd( t_commands *cmd); ////
///   
void print_lines(int i, char **str, int out);
int bult_echo(  t_commands *cmd);////
////
int	ft_pwd(void);////

///  
int buit_cd(  t_commands *cmd);
// void determine_exit_code(char **str);
// int	is_str_digit(char *str);
// void	free_tools(t_data *data);
int bult_exit(char **args);/////

///
char	**whileloop_var(char **arr, char **rtn, char *str);
char	**var(char **arr, char *str);
int	unset_error(t_commands *cmd);
int	bult_unset(t_data *data, t_commands *cmd);////

///
int	variable_exist(t_data *data, char *str);
int	check_parameter(char *str);
int	export_error(char *c);
char	**whileloop_add_var(char **arr, char **rtn, char *str);
char	**add_var(char **arr, char *str);
int	bult_export(t_data *data, t_commands *cmd);
int	bult_env(t_data *data, t_commands *cmd);


#endif
