/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:14:02 by hamza_hat         #+#    #+#             */
/*   Updated: 2025/04/03 16:44:09 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//! ft_safe_malloc:
#include <stdio.h>
#include <stdlib.h>

//? Macros for ft_safe_malloc keys:
#define ALLOCATE 1
#define FREE_ALL 0
#define FREE_ONE 2

//? ft_saf_malloc struct:
typedef struct s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}				t_mem_node;

//? Zero out a block of memory.
static void	ft_bzero(void *s, size_t len)
{
	unsigned char	*tmp; // Temporary pointer to traverse the memory block.

	tmp = (unsigned char *)s; // Cast the input pointer to unsigned char.
	while (len--)
		*tmp++ = 0; // Set each byte to 0.
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

//? Free a specific memory block and update the tracking list
static void free_specific_node(t_mem_node **lst, void *to_delete)
{
    t_mem_node	*current;
    t_mem_node	*prev;

    if (!lst || !*lst || !to_delete)
        return;

    current = *lst;
    prev = NULL;

    // Search for the node that contains the address
    while (current)
    {
        if (current->address == to_delete)
        {
            // Found the node, free the memory
            free(current->address);

            // Remove node from the list
            if (prev)
                prev->next = current->next;
            else
                *lst = current->next;

            // Free the node itself
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

//? Allocate memory, track it, and handle failures safely.
void	*ft_safe_malloc(size_t size, int key, int exit_status, void *to_delete)
{
	static t_mem_node	*mem_node; // Static list to track allocated memory.
	void				*ptr; // Pointer to the allocated memory block.

	ptr = NULL;
	// Allocate memory and track it.
	if (key == ALLOCATE)
	{
		ptr = malloc(size);  // Allocate memory.
		if (!ptr)
			free_list(&mem_node, -1);  // Free all memory and exit if allocation fails.
		lst_add_back_malloc(&mem_node, ptr); // Add the allocated memory block to the tracking list.
		ft_bzero(ptr, size); // Zero out the allocated memory.
	}
	else if (key == FREE_ALL) // Free all tracked memory and exit.
		free_list(&mem_node, exit_status);
	else if (key == FREE_ONE) // update all the nodes that contain  NULL ( freed )
		free_specific_node(&mem_node, to_delete);
	return (ptr); // Return the allocated memory block.
}


//? int main :
void f(){system("leaks a.out");}
#include <stdio.h>
int main(void)
{
	atexit(f);

    int *a = ft_safe_malloc(sizeof(int), 1, 1, 0);
    int *b = ft_safe_malloc(sizeof(int), 1, 1, 0);
    int *c = ft_safe_malloc(sizeof(int), 1, 1, 0);

    *a = 10;
    *b = 20;
    *c = 30;

	printf("a = %p\n", a);
	a = ft_safe_malloc(0, 2, 1, a);
	c = ft_safe_malloc(0, 2, 1, c);
	b = ft_safe_malloc(0, 2, 1, b);
	printf("%p %p %p\n", a, b, c);
    ft_safe_malloc(0, 0, 0, 0);

    return 0;
}
