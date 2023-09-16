/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 03:37:02 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/14 03:47:45 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *remove_beg_end(char *str)
{
    int     start;
    int     end;
    int     idx;
    char    *ptr;

    start = 0;
    end = ft_strlen(str) - 1;
    idx = 0;
    ptr = malloc(sizeof(char) * ft_strlen(str));
    while (str[start] && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n'))
        start++;
    while (str[end] && end > 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
        end--;
    while(str[start] && start <= end)
    {
        ptr[idx] = str[start];
        idx++;
        start++;
    }
    ptr[idx] = '\0';
    return (ptr);
}