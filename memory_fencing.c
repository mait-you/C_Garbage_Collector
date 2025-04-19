/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fencing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:46:19 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 16:14:16 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc_safety.h"

/**
 * @brief Sets up guard bytes at the beginning and end of a memory block
 * 
 * @param ptr Pointer to the allocated memory (including guard areas)
 * @param size Total size of the user's requested memory
 * @return void* Pointer to the usable memory area (after front guard)
 */
static void *setup_memory_fencing(void *ptr, size_t total_size)
{
    if (!ptr)
        return NULL;
    ft_memset(ptr, GUARD_PATTERN, GUARD_SIZE);
    ft_memset((unsigned char *)ptr + GUARD_SIZE + total_size, GUARD_PATTERN, GUARD_SIZE);
    return ((unsigned char *)ptr + GUARD_SIZE);
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
void	*allocate_ptr_memory_fencing(size_t size[2], void **ptr_array)
{
	void	*ptr;
	void	*user_ptr;

	ptr = ft_calloc(size[0] + (GUARD_SIZE * 2), size[1]);
	if (!ptr)
	{
		free_all(ptr_array, size[0] * size[1]);
		return (NULL);
	}
	user_ptr = setup_memory_fencing(ptr, size[0] * size[1]);
	ft_memset(user_ptr, 0, size[0] * size[1]);
	if (!add_to_tracking(ptr_array, ptr))
	{
		free(ptr);
		free_all_memory_fencing(ptr_array, size[0] * size[1]);
		return (NULL);
	}
	return (user_ptr);
}

/**
 * @brief Checks if memory guard bytes are intact
 * 
 * @param user_ptr Pointer to the usable memory area
 * @param size Total size of the user's requested memory
 * @return int 1 if memory is intact, 0 if corrupted
 */
static int	check_memory_fencing(void *user_ptr, size_t total_size)
{
	unsigned char	*start_guard;
	unsigned char	*end_guard;
	int				i;

	if (!user_ptr)
		return (0);
	start_guard = (unsigned char *)user_ptr - GUARD_SIZE;
	end_guard = (unsigned char *)user_ptr + total_size;
	i = 0;
	while (i < GUARD_SIZE)
	{
		if (start_guard[i] != GUARD_PATTERN)
			return (1);
		if (end_guard[i] != GUARD_PATTERN)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Get the original malloc pointer from a user pointer
 * 
 * @param user_ptr The pointer returned to the user
 * @return void* The original pointer returned by malloc
 */
static void *get_original_ptr(void *user_ptr)
{
    if (!user_ptr)
        return (NULL);
    return ((unsigned char *)user_ptr - GUARD_SIZE);
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
void	*free_specific_memory_fencing(void **ptr_array, const void *to_delete, size_t size)
{
	int		i;
	void	*original_ptr;

    i = 0;
	original_ptr = get_original_ptr((void *)to_delete);
    while (i < MAX_ALLOCATIONS)
	{
        if (ptr_array[i] == original_ptr)
		{
            if (check_memory_fencing((void *)to_delete, size))
                ft_putendl_fd("Error: Memory corruption detected", STDERR_FILENO);
            free(original_ptr);
            ptr_array[i] = NULL;
            return NULL;
        }
        i++;
    }
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
void	*free_all_memory_fencing(void **ptr_array, size_t size)
{
	int	i;
	void	*original_ptr;

	i = 0;
	
	while (i < MAX_ALLOCATIONS)
	{
		if (ptr_array[i])
		{
			original_ptr = get_original_ptr((void *)ptr_array[i]);
			if (check_memory_fencing(original_ptr, size))
                ft_putendl_fd("Error: Memory corruption detected", STDERR_FILENO);
			free(ptr_array[i]);
			ptr_array[i] = NULL;
		}
		i++;
	}
	return (NULL);
}
