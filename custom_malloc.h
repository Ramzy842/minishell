/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_malloc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:47:06 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 23:50:36 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_MALLOC_H
# define CUSTOM_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

enum e_a_types {
	ALLOC,
	FREE,
	FREE_ALL,
	T_SIZE,
};

struct s_address
{
	void					*ptr;
	unsigned int			size;
	bool					dealloc;
	struct s_address		*next;
	struct s_address		*prev;
};
typedef struct s_address	t_address;

void		*custom_malloc(unsigned int size, void	*free_ptr,
				int type, uint32_t *t_size);
t_address	*create_node(void *ptr, unsigned int size);
void		add_node_back(t_address **head, t_address *node);
void		destroy_node(t_address *node);
void		print_string(char *string);
void		print_number(unsigned int number);
void		print_str_with_int(char *string, unsigned int n);
#endif