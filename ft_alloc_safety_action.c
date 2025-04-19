/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_safety_action.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:46:19 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 17:01:00 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc_safety.h"

/**
 * @brief Reallocates memory for a specific pointer without using realloc,
 *        manually allocating new memory, copying the old data, and freeing 
 *        the old pointer.
 * 
 * @param size The size of the memory to be allocated (array of 2 size_t 
 *        elements).
 * @param ptr_array The array of pointers being tracked.
 * @param to_delete The pointer to be reallocated.
 * @return void* The reallocated memory or NULL if allocation failed.
 */
void	*realloc_ptr(size_t size[2], void **ptr_array, void *to_delete)
{
	void	*new_ptr;

	new_ptr = allocate_ptr(size, ptr_array);
	if (!new_ptr)
		return (NULL);
	if (to_delete)
	{
		ft_memcpy(new_ptr, to_delete, size[0] * size[1]);
		free_specific(ptr_array, to_delete, size[0] * size[1]);
	}
	return (new_ptr);
}

/**
 * @brief Counts the number of non-NULL pointers in the tracking array.
 * 
 * @param ptr_array The array of pointers being tracked.
 * @return int The number of active allocations.
 */
int	get_allocation_count(void **ptr_array)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (ptr_array[i] != NULL)
			count++;
		i++;
	}
	return (count);
}

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
void	*free_specific(void **ptr_array, const void *to_delete, size_t size)
{
	int	i;

	if (MEMORY_FENCING)
		free_specific_memory_fencing(ptr_array, to_delete, size);
	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (ptr_array[i] == to_delete)
		{
			free(ptr_array[i]);
			ptr_array[i] = NULL;
			return (NULL);
		}
		else if (ptr_array[i] == NULL && to_delete == ptr_array[i])
		{
			ft_putendl_fd(
				"Warning: Attempt to free an already freed", STDERR_FILENO);
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
void	*free_all(void **ptr_array, size_t size)
{
	int	i;

	if (MEMORY_FENCING)
		free_all_memory_fencing(ptr_array, size);
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
 * @brief Allocates memory using `ft_calloc`, then adds the allocated pointer 
 *        to the tracking array. If allocation fails or the array is full, 
 *        it frees the memory to avoid leaks.
 * 
 * @param size The size of the memory to be allocated (array of 2 size_t
 *        elements).
 * @param ptr_array The array of pointers being tracked.
 * @return void* The allocated memory or NULL if allocation fails.
 */
void	*allocate_ptr(size_t size[2], void **ptr_array)
{
	void	*ptr;

	if (MEMORY_FENCING)
		allocate_ptr_memory_fencing(size[0] * size[1], ptr_array);
	ptr = ft_calloc(size[0], size[1]);
	if (!ptr)
	{
		free_all(ptr_array, size[0] * size[1]);
		return (NULL);
	}
	if (!add_to_tracking(ptr_array, ptr))
	{
		free(ptr);
		free_all(ptr_array, size[0] * size[1]);
		return (NULL);
	}
	return (ptr);
}
