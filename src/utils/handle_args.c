/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:10:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:59:31 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_args(char **args)
{
	int		x;
	char	*temp;
	char	*str;

	x = 0;
	str = custom_malloc(sizeof(char) * 1, NULL, ALLOC, NULL);
	str[0] = '\0';
	while (args[x])
	{
		temp = ft_strjoin(str, args[x]);
		free(str);
		str = temp;
		temp = ft_strjoin(str, " ");
		free(str);
		str = temp;
		x++;
	}
	return (str);
}
