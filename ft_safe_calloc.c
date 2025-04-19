/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:46:19 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 13:26:51 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_safe_calloc.h"

/**
 * @brief Frees a specific pointer from the tracking array. If the pointer is 
 *        not found in the array, it frees it directly. It also ensures that 
 *        no memory leaks occur by setting the corresponding array element to 
 *        NULL after freeing.
 * 
 * @param ptr_array The array of pointers being tracked.
 * @param to_delete The pointer to be freed.
 * @return void* NULL after the pointer is freed.
 */
static void	*free_specific(void **ptr_array, const void *to_delete)
{
	int	i;

	if (!to_delete)
		return (NULL);
	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (ptr_array[i] == to_delete)
		{
			free(ptr_array[i]);
			ptr_array[i] = NULL;
			return (NULL);
		}
		i++;
	}
	free((void *)to_delete);
	return (NULL);
}

/**
 * @brief Frees all the pointers in the tracking array and sets them to NULL 
 *        to ensure no memory leaks. It is called when all memory should be
 *        freed.
 * 
 * @param ptr_array The array of pointers being tracked.
 * @return void* NULL after all memory is freed.
 */
static void	*free_all(void **ptr_array)
{
	int	i;

	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (ptr_array[i])
		{
			free(ptr_array[i]);
			ptr_array[i] = NULL;
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief Adds a pointer to the tracking array if there's space. If the array 
 *        is full, it prints an error message and returns 0. This function 
 *        ensures the array doesn't overflow.
 * 
 * @param ptr_array The array where pointers are tracked.
 * @param ptr The pointer to be added to the array.
 * @return int Returns 1 if the pointer was successfully added, 0 if the array
 *        is full.
 */
static int	add_to_tracking(void **ptr_array, void *ptr)
{
	int	i;

	if (!ptr)
		return (0);
	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (ptr_array[i] == NULL)
		{
			ptr_array[i] = ptr;
			return (1);
		}
		i++;
	}
	ft_putendl_fd("Error: Maximum allocation limit reached", STDERR_FILENO);
	return (0);
}

/**
 * @brief Allocates memory using `ft_calloc`, then adds the allocated pointer 
 *        to the tracking array. If allocation fails or the array is full, 
 *        it frees the memory to avoid leaks.
 * 
 * @param size The size of the memory to be allocated (array of 2 size_t
 *        elements).
 * @param ptr_array The array of pointers being tracked.
 * @return void* The allocated memory or NULL if allocation fails.
 */
static void	*allocate_ptr(size_t size[2], void **ptr_array)
{
	void	*ptr;

	ptr = ft_calloc(size[0], size[1]);
	if (!ptr)
	{
		free_all(ptr_array);
		return (NULL);
	}
	if (!add_to_tracking(ptr_array, ptr))
	{
		free(ptr);
		free_all(ptr_array);
		return (NULL);
	}
	return (ptr);
}

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
void	*ft_safe_calloc_thread_safety(
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
		ptr = free_all(ptr_array);
	else if (action == FREE_ONE)
		ptr = free_specific(ptr_array, to_delete);
	pthread_mutex_unlock(&init_mutex);
	return (ptr);
}
