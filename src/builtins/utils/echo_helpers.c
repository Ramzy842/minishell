/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:46:21 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/11 04:08:00 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char    *extract_echo_args(char *input, int start)
{
    char    *str;
    int     idx;

    str = malloc(sizeof(char) * (ft_strlen(input) - start) + 1);
    idx = 0;
    while (input[start])
    {
        str[idx] = input[start];
        start++;
        idx++;
    }
    str[idx] = '\0';
    return str;
}

int is_between_quotes(char *str)
{
    if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
        return (1);
    return (0);
}

int     count_double_quotes(char *str)
{
    int x = 0;
    int count = 0;

    while (str[x])
    {
        if (str[x] == '\"')
            count++;
        x++;
    }
    return (count);
}

char    *remove_double_quotes(char *str)
{
    int     x;
    int     idx;
    char    *ptr;
    
    x = 0;
    idx = 0;
    ptr = malloc(ft_strlen(str) * sizeof(char) + 1);
    while (str[x])
    {
        if (str[x] != '\"')
        {
            ptr[idx] = str[x];
            idx++;
        }
        x++;
    }
    ptr[idx] = '\0';
    return (ptr);
}

void    echo_option_n(char **args)
{
    int x;

    if (args[1])
    {
        x = 1;
        while (args[x + 1])
        {
            printf("%s ", args[x]);
            x++;
        }
        printf("%s", args[x]);
    }
}

void    echo_without_option_n(char **args, char *input)
{
    int x;

    x = 0;
    if (count_double_quotes(extract_echo_args(input, 5)) != 0)
    {
        char *str = remove_double_quotes(extract_echo_args(input, 5));
        while (str[x])
        {
            printf("%c", str[x]);
            x++;
        }
        printf("\n");
    }
    else
    {
        while (args[x + 1])
        {
            printf("%s ", args[x]);
            x++;
        }
        printf("%s\n", args[x]);
    }  
}