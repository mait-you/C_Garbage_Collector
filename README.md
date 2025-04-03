# ft_safe_malloc

ft_saf_malloc

ft_saf_malloc is a memory management utility designed to simplify dynamic memory allocation in C programs. It provides a safer and more controlled approach to memory allocation and deallocation, reducing the risk of memory leaks and segmentation faults.

Features

Centralized Memory Management: All dynamically allocated memory is tracked, allowing for easy deallocation at any point in the program.
Automatic Cleanup: Ensures that all allocated memory is freed upon program termination or when explicitly requested.
Error Handling: If memory allocation fails, the utility handles the error gracefully by freeing all previously allocated memory and exiting the program.
Function:

void *ft_malloc(size_t size, int key, int exit_status);

Allocates memory and manages it internally.

Parameters:

size: The size of memory to allocate in bytes.

key: Determines the operation mode:

1: Allocates memory of the given size.

0: Frees all allocated memory and exits the program with the provided exit_status.

exit_status: The exit status code used when freeing memory and terminating the program (applicable when key is 0).

Returns: A pointer to the allocated memory if key is 1; otherwise, NULL.
