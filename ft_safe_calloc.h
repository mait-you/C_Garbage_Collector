/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_calloc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:47 by mait-you          #+#    #+#             */
/*   Updated: 2025/04/19 13:27:43 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SAFE_CALLOC_H
# define FT_SAFE_CALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define MAX_ALLOCATIONS 1024

typedef enum e_action
{
	ALLOCATE,
	FREE_ALL,
	FREE_ONE
}	t_action;

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_safe_calloc(\
	size_t size[2], t_action key, int exit_status, void *to_delete);

#endif