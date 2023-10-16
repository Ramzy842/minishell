/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:08:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/15 14:58:36 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../../minishell.h"

char	*find_path_ret(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], str, ft_strlen(str)))
			return (ft_substr(data->envp[i], ft_strlen(str),
					ft_strlen(data->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}
void	change_path(t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(data->pwd);
 	free(data->old_pwd);
	data->old_pwd = tmp;
	free(data->pwd);
	data->pwd = getcwd(NULL, sizeof(NULL));
}


int	specific_path(t_data *data, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, data);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", data->pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7) && data->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", data->old_pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		i++;
	}
}

int	bult_cd(t_data *data, t_commands *cmd)
{
	int		ret;

	if (!cmd->command_args[1])
		ret = specific_path(data, "HOME=");
	else if (ft_strncmp(cmd->command_args[1], "-", 1) == 0)
		ret = specific_path(data, "OLDPWD=");
	else
	{
		ret = chdir(cmd->command_args[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->command_args[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(data);
	add_path_to_env(data);
	return (EXIT_SUCCESS);
}


int buit_cd(t_data *data, t_commands *cmd) {
	(void) *data;
	printf("kakaka\n");
    if (cmd->command_args[1] == NULL) {
        // Handle "cd" without arguments (cd to home directory)
        const char* home_dir = getenv("HOME");
        if (home_dir != NULL) {
            if (chdir(home_dir) != 0) {
				printf("error\n");
                perror("cd");
                return 1; // Return a non-zero value for failure
            }
        } else {
            printf("HOME directory not set in the environment.\n");
			printf("error\n");
            return 1; // Return a non-zero value for failure
        }
    } else {
        // Handle "cd" with a directory argument
        if (chdir(cmd->command_args[1]) != 0) {
            perror("cd");
            return 1; // Return a non-zero value for failure
        }
    }
	printf("successs\n");
    return 0; // Return 0 for success
}