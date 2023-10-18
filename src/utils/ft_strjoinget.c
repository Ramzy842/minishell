/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinget.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:44:57 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/18 05:01:06 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoinget(char *s1, char *s2)
{
	int		lenth1;
	int		lenth2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	lenth1 = ft_strlen(s1);
	lenth2 = ft_strlen(s2);
	result = ft_calloc(lenth1 + lenth2 + 1, 1);
	if (result)
	{
		ft_memmove(result, s1, lenth1);
		ft_memmove(result + lenth1, s2, lenth2);
	}
	return (result);
}
