/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:21:46 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/12 20:22:06 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_strjoin_2d(char *s1, char **s2, int s2_size) {
    char *ptr;
    int len_s1 = strlen(s1);
    int total_length = len_s1;

    // Calculate the total length of the strings in s2
    for (int i = 0; i < s2_size; i++) {
        total_length += strlen(s2[i]);
    }

    ptr = (char *)malloc((total_length + 1) * sizeof(char));
    if (ptr == NULL) {
        return NULL;
    }

    int x = 0;

    // Copy s1 to the result
    for (int i = 0; s1[i] != '\0'; i++) {
        ptr[x] = s1[i];
        x++;
    }

    // Copy each string in s2 to the result
    for (int i = 0; i < s2_size; i++) {
        for (int j = 0; s2[i][j] != '\0'; j++) {
            ptr[x] = s2[i][j];
            x++;
        }
    }

    ptr[x] = '\0';
    return ptr;
}