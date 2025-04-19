/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_safety.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:47 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 16:58:28 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALLOC_SAFETY_H
# define FT_ALLOC_SAFETY_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef MEMORY_FENCING
#  define MEMORY_FENCING false
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

void	*allocate_ptr_memory_fencing(size_t size[2], void **ptr_array);
void	*free_all_memory_fencing(void **ptr_array, size_t size);
void	*free_specific_memory_fencing(\
	void **ptr_array, const void *to_delete, size_t size);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putendl_fd(char *s, int fd);
int		add_to_tracking(void **ptr_array, void *ptr);

void	*realloc_ptr(size_t size[2], void **ptr_array, void *to_delete);
void	*allocate_ptr(size_t size[2], void **ptr_array);
void	*free_all(void **ptr_array, size_t size);
void	*free_specific(void **ptr_array, const void *to_delete, size_t size);
int		get_allocation_count(void **ptr_array);
void	*ft_alloc_safety(\
	size_t size[2], t_action action, void *to_delete);

#endif
