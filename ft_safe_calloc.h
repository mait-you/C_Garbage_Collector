/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_calloc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:47 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/18 18:50:48 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SAFE_CALLOC_H
# define FT_SAFE_CALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef MAX_ALLOCATIONS
#  define MAX_ALLOCATIONS 1024
# endif

typedef enum e_keys
{
	ALLOCATE,
	FREE_ALL,
	FREE_ONE
}	t_keys;

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_safe_calloc(\
	size_t size[2], t_keys key, int exit_status, void *to_delete);

#endif