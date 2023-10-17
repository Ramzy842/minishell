/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:50:57 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/15 08:41:35 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../minishell.h"
char	**whileloop_var(char **arr, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
				&& str[equal_sign(arr[i])] == '\0'
				&& arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_arr(rtn);
				return (rtn);
			}
			j++;
		}	
		i++;
	}
	return (rtn);
}

char	**var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_var(arr, rtn, str);
	return (rtn);
}

int	unset_error(t_commands *cmd)
{
	int		i;

	i = 0;
	if (!cmd->command_args[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (cmd->command_args[1][i])
	{
		if (cmd->command_args[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd->command_args[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equal_sign(cmd->command_args[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	bult_unset(t_data *data, t_commands *cmd)
{
	char	**tmp;

	if (unset_error(cmd) == 1)
		return (EXIT_FAILURE);
	else
	{
		tmp = var(data->envp, cmd->command_args[1]);
		free_arr(data->envp);
		data->envp = tmp;
	}
	return (EXIT_SUCCESS);
}