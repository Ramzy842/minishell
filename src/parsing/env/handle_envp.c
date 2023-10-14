/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:06:49 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:07:29 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void handle_envp(t_data *data)
{
	int		x;
	char	*envp_path;
	char	*temp;

	envp_path = NULL;
	temp = NULL;
	envp_path = extract_path(data->envp);
	data->paths = ft_split(envp_path, ':');
	free(envp_path);
	x = 0;
	while (data->paths[x])
	{ 
		if (ft_strncmp(&data->paths[x][ft_strlen(data->paths[x]) - 1],
			"/", 1) != 0)
		{
			temp = ft_strjoin(data->paths[x], "/");
			free(data->paths[x]);
			data->paths[x] = temp;
		}
		x++;
	}
}