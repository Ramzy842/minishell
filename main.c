/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/02 11:19:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	minishell_loop(t_data *data);

int	reset_data(t_data *data)
{
	//ft_simple_cmdsclear(&data->simple_cmds);
	free(data->shell_input);
	//if (data->pid)
	//	free(data->pid);
	//free_arr(data->paths);
	initialize_data(data);
	data->reset = 1;
	printf("performing reset\n");
	minishell_loop(data);
	return (1);
}

char *show_current_path(char *working_dir)
{
	working_dir = print_current_dir();
	working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
	working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
	return (working_dir);
}

int	minishell_loop(t_data *data)
{
	char    *working_dir = NULL;
	char	*temp;

	working_dir = show_current_path(working_dir);
	data->shell_input = readline(working_dir);
	temp = ft_strtrim(data->shell_input, " ");
	free(data->shell_input);
	data->shell_input = temp;
	if (!data->shell_input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(&data->shell_input[0]) == '\0')
		return (reset_data(data));
	add_history(data->shell_input);
	if (!quotes_are_matching(data->shell_input))
		//return (ft_error(2, data));
	{
		printf("error in quotes\n");
		return (EXIT_FAILURE);		
	}
	if (!tokens_reader(data))
		//return (ft_error(1, data)); -----> this is correct
	{
		printf("tokenization error\n");
	}
	//parser(data);
	//prepare_executor(data);
	printf("executing command\n");
	printer(data);
	reset_data(data);
	return (1);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	(void) envp;
	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments\n");
		exit(0);
	}
	//data.envp = ft_arrdup(envp);
	//find_pwd(&tools);
	initialize_data(&data);
	minishell_loop(&data);
	return (0);
}
