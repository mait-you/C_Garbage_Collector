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

// creat a new node and assigne the ptr to it and add it the linked lis
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
		return ((void)(*lst = tmp));
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
	if (key == 1) // key = 1 => allocate memory
	{
		if (!(ptr = malloc(size)))
			free_list(&mem_node, 1);
		lst_add_back(&mem_node, ptr);
	}
	if (key == 0) // key = 0 => free memory
		free_list(&mem_node, exit_status);
	return (ptr);
}
