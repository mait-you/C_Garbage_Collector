/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_safety.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:46:19 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 16:00:34 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc_safety.h"

/**
 * @brief Safely allocates, frees all allocations, or frees a specific
 *  	  allocation based on the provided action. This function helps manage
 *        memory allocations and deallocations efficiently while tracking the 
 *        allocations to prevent memory leaks.
 * 
 * @param size The size of the memory to be allocated (array of 2 size_t
 * 		  elements).
 * @param action The action to be performed (ALLOCATE, FREE_ALL, or FREE_ONE).
 * @param to_delete The pointer to delete (used when action is FREE_ONE).
 * @return void* The allocated memory, NULL if an error occurs or if the memory 
 *               was freed successfully.
 */
void	*ft_alloc_safety(
	size_t size[2], t_action action, void *to_delete
	)
{
	static void				*ptr_array[MAX_ALLOCATIONS] = {NULL};
	static pthread_mutex_t	init_mutex = PTHREAD_MUTEX_INITIALIZER;
	void					*ptr;

	pthread_mutex_lock(&init_mutex);
	ptr = NULL;
	if (action == ALLOCATE)
		ptr = allocate_ptr(size, ptr_array);
	else if (action == FREE_ALL)
		ptr = free_all(ptr_array, size[0] * size[1]);
	else if (action == FREE_ONE)
		ptr = free_specific(ptr_array, to_delete, size[0] * size[1]);
	else if (action == GET_USAGE)
		ptr = (void *)(uintptr_t)get_allocation_count(ptr_array);
	else if (action == REALLOC)
		ptr = realloc_ptr(size, ptr_array, to_delete);
	pthread_mutex_unlock(&init_mutex);
	return (ptr);
}
