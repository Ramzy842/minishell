/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:10:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 12:11:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_args(char **args)
{
	int		x;
	char	*temp;
	char	*str;

	x = 0;
	str = malloc(sizeof(char) * 1);
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
