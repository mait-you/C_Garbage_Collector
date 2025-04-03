/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saf_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:14:02 by hamza_hat         #+#    #+#             */
/*   Updated: 2025/04/03 14:18:51 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//! ft_safe_malloc:
#include <stdio.h>
#include <stdlib.h>
void	*ft_safe_malloc(size_t size, int key, int exit_status);

//? ft_saf_malloc struct:
typedef struct	s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}				t_mem_node;

//? update the lst and free all nodes == NULL
static void	update_lst(t_mem_node **lst)
{
	t_mem_node	*current;
	t_mem_node	*prev;
	t_mem_node	*tmp;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current->address == NULL)
		{
			tmp = current->next;
			free(current);
			if (prev)
				prev->next = tmp; // Link previous node to the next valid node
			else
				*lst = tmp; // Update head if the first node is removed
			current = tmp;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

//? use: ft_free((void **)&ptr); ( good practice to case it to (void **))
void	ft_free(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ft_safe_malloc(0, 2, 1);
	}
}

//? Zero out a block of memory.
static void ft_bzero(void *s, size_t len)
{
	unsigned char *tmp;  // Temporary pointer to traverse the memory block.

	tmp = (unsigned char *)s;  // Cast the input pointer to unsigned char.
	while (len--)
		*tmp++ = 0;  // Set each byte to 0.
}

//? Free all allocated memory in the memory tracking list and exit.
static void free_list(t_mem_node **list, int exit_status)
{
	t_mem_node *tmp;  // Temporary pointer to traverse the memory tracking list.

	// Free all nodes in the memory tracking list.
	while (*list)
	{
		tmp = (*list)->next;  // Save the next node.
		free((*list)->address);  // Free the memory block tracked by the current node.
		free(*list);  // Free the current node.
		*list = tmp;  // Move to the next node.
	}
	exit(exit_status);  // Exit the program with the specified status.
}

//? Add a new memory block to the memory tracking list.
static void lst_add_back_malloc(t_mem_node **lst, void *value)
{
	t_mem_node *last;  // Pointer to the last node in the list.
	t_mem_node *tmp;   // Temporary pointer for the new node.

	// Check if the list or value is NULL.
	if (!lst || !value)
		return;

	// Allocate memory for the new node.
	tmp = malloc(sizeof(t_mem_node));
	if (!tmp)
		free_list(lst, -1);  // Free all memory and exit if allocation fails.

	// Initialize the new node.
	tmp->address = value;  // Store the memory block address.
	tmp->next = NULL;      // Set the next pointer to NULL.

	// If the list is empty, set the new node as the head.
	if (!*lst)
	{
		*lst = tmp;
		return;
	}

	// Traverse to the end of the list.
	last = *lst;
	while (last->next)
		last = last->next;

	// Add the new node to the end of the list.
	last->next = tmp;
}

//? Allocate memory, track it, and handle failures safely.
void	*ft_safe_malloc(size_t size, int key, int exit_status)
{
	static t_mem_node	*mem_node; // Static list to track allocated memory.
	void				*ptr; // Pointer to the allocated memory block.

	ptr = NULL;
	// Allocate memory and track it.
	if (key == 1)
	{
		ptr = malloc(size);  // Allocate memory.
		if (!ptr)
			free_list(&mem_node, -1);  // Free all memory and exit if allocation fails.
		lst_add_back_malloc(&mem_node, ptr); // Add the allocated memory block to the tracking list.
		ft_bzero(ptr, size); // Zero out the allocated memory.
	}
	else if (key == 0) // Free all tracked memory and exit.
		free_list(&mem_node, exit_status);
	else if (key == 2) // update all the nodes that contain  NULL ( freed )
		update_lst(&mem_node);
	return (ptr); // Return the allocated memory block.
}


//? int main :
///*

// int main (void)
// {
// 	int *nb_1 = ft_safe_malloc(sizeof(int) * 1, 1, 1);
// 	int *nb_2 = ft_safe_malloc(sizeof(int) * 1, 1, 1);
// 	int *nb_3 = ft_safe_malloc(sizeof(int) * 1, 1, 1);

// 	*nb_1 = 1337;
// 	*nb_2 = 42;
// 	*nb_3 = 21;

// 	printf("nb_1 = %d\n", *nb_1);
// 	printf("nb_2 = %d\n", *nb_2);
// 	printf("nb_3 = %d\n", *nb_3);

// 	ft_free((void **)&nb_1);
// 	ft_free((void **)&nb_2);
// 	// ft_free((void **)&nb_3);
// //? free the lst:
// 	ft_safe_malloc(0,0,0);
// 	return (0);
// }
#include <stdio.h>
int main(void)
{
    // Allocate three memory blocks
    int *a = ft_safe_malloc(sizeof(int), 1, 1);
    // int *b = ft_safe_malloc(sizeof(int), 1, 1);
    // int *c = ft_safe_malloc(sizeof(int), 1, 1);
    //
    // *a = 10;
    // *b = 20;
    // *c = 30;

    //printf("a = %d, b = %d, c = %d\n", *a, *b, *c);

    // Free memory
    ft_free((void **)&a);
    // ft_free((void **)&b);
    // ft_free((void **)&c);
    //
    // Free tracking list before exiting
    ft_safe_malloc(0, 0, 0);

    return 0;
}

//*/