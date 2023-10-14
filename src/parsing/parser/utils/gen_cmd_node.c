/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:05:30 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:05:37 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

t_commands	*gen_cmd_node()
{
	t_commands* ret = malloc(sizeof(t_commands));
	ft_memset(ret, 0, sizeof(t_commands));
	ret->out = 1;
	return ret;
}