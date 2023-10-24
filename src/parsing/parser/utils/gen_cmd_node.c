/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:05:30 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:20:25 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

t_commands	*gen_cmd_node(void)
{
	t_commands	*ret;

	ret = custom_malloc(sizeof(t_commands), NULL, ALLOC, NULL);
	ft_memset(ret, 0, sizeof(t_commands));
	ret->out = 1;
	return (ret);
}
