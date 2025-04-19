/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_safety.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:47 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 15:00:10 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CALLOC_SAFETY_H
# define FT_CALLOC_SAFETY_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef MEMEORY_FENCING
#  define MEMEORY_FENCING false
# endif

# define MAX_ALLOCATIONS 1024
# define GUARD_SIZE 8
# define GUARD_PATTERN 0xAB

typedef enum e_action
{
	ALLOCATE,
	FREE_ALL,
	FREE_ONE,
	GET_USAGE,
	REALLOC
}	t_action;

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*allocate_ptr(size_t size[2], void **ptr_array);
int		add_to_tracking(void **ptr_array, void *ptr);
void	*free_all(void **ptr_array);
void	*free_specific(void **ptr_array, const void *to_delete);
int		get_allocation_count(void **ptr_array);
void	*ft_alloc_safety(
	size_t size[2], t_action action, void *to_delete
	);

#endif