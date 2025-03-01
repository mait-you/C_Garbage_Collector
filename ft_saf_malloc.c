/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saf_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza_hat <hamza_hat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:14:02 by hamza_hat         #+#    #+#             */
/*   Updated: 2025/03/01 20:15:08 by hamza_hat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// ft_saf_malloc struct:
typedef struct s_mem_node
{
	void *address;
	struct s_mem_node *next;
} t_mem_node;

// free all allocated memory:
void	free_list(t_mem_node **list, int exit_status)
{
	t_mem_node *tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->address);
		free(*list);
		*list = tmp;
	}
	exit(exit_status);
}

void	lst_add_back(t_mem_node **lst, void *value)
{
	t_mem_node *last;
	t_mem_node *tmp;

	if (!lst || !value)
		return ;
	tmp = malloc(sizeof(t_mem_node));
	if(!tmp)
		free_list(lst, 1);
	tmp->address = value;
	tmp->next = NULL;
	if (!*lst)
	{
		*lst = tmp;
		return;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

void	*ft_malloc(size_t size, int key, int exit_status)
{
	// Static pointer to the head of the list
	static t_mem_node *mem_node = NULL;
	void	*ptr;

	ptr = NULL;
	// Key == 1 → Allocate memory
	if (key == 1)
	{
		if (!(ptr = malloc(size)))
			free_list(&mem_node, 1);
		lst_add_back(&mem_node, ptr);
	}
	if (key == 0)
		free_list(&mem_node, exit_status);
	return (ptr);
}
