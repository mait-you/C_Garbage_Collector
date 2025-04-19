/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_safety_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:25:38 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 16:59:36 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc_safety.h"

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
int	add_to_tracking(void **ptr_array, void *ptr)
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
 * @brief 
 * 
 * @param b 
 * @param c 
 * @param len 
 * @return void* 
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- > 0)
		*(ptr++) = (unsigned char)c;
	return (b);
}

/**
 * @brief 
 * 
 * @param count 
 * @param size 
 * @return void* 
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

/**
 * @brief 
 * 
 * @param dst 
 * @param src 
 * @param n 
 * @return void* 
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*ptr;

	if (!src && !dst)
		return (0);
	i = 0;
	ptr = (char *)dst;
	while (i < n)
	{
		*(ptr++) = *((const char *)src++);
		i++;
	}
	return (dst);
}

/**
 * @brief 
 * 
 * @param s 
 * @param fd 
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd == -1)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}
