/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:08:24 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/14 11:08:31 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char* ft_strncpy(char* dest, const char* src, size_t n)
{
    char* original_dest = dest;

    while (n > 0 && *src != '\0')
	{
        *dest++ = *src++;
        n--;
    }

    // Fill the remaining space with null bytes if necessary
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }

    return (original_dest);
}