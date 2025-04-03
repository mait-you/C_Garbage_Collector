# 🛠️ ft_safe_malloc - A Simple Garbage Collector in C

## 📌 Overview
`ft_safe_malloc` is a custom memory allocator that acts as a **garbage collector** for C programs. It helps in **tracking and managing memory allocations** to prevent memory leaks and **automatically free memory when needed**. 🚀

## 🔥 Features
✅ **Automatic memory tracking** - Keeps track of all allocated memory.
✅ **Safe allocation** - If allocation fails, it automatically frees all memory and exits.
✅ **Free one or all allocations** - You can free a specific allocation or clear everything.
✅ **Prevents memory leaks** - Ensures proper memory management.

---

## 📜 How It Works
The function `ft_safe_malloc` operates based on a **key system**:

| Key          | Description |
|-------------|------------|
| `ALLOCATE` (1) | Allocate memory and track it. |
| `FREE_ALL` (0) | Free all allocated memory and exit. |
| `FREE_ONE` (2) | Free a specific memory block. |

---

📌 Prototype

void *ft_safe_malloc(size_t size, int key, int exit_status, void *to_delete);

🔍 Explanation of Parameters:

size: The number of bytes to allocate (ignored for FREE_ONE and FREE_ALL).

key: Determines the operation (ALLOCATE, FREE_ONE, or FREE_ALL).

exit_status: Used when FREE_ALL is called to specify the exit status.

to_delete: The pointer to free when FREE_ONE is used.

## 🏗️ Usage

### 🚀 Allocating Memory
To allocate memory, use:
```c
int *ptr = (int *)ft_safe_malloc(sizeof(int), ALLOCATE, 1, NULL);
```
✅ This allocates memory and tracks it.
✅ If allocation fails, all tracked memory is freed, and the program exits.

### 🗑️ Freeing a Specific Pointer
To free a single allocated block:
```c
ft_safe_malloc(0, FREE_ONE, 1, ptr);
```
✅ This removes `ptr` from tracking and frees its memory.

### 💥 Freeing All Allocations
To free everything at once and exit:
```c
ft_safe_malloc(0, FREE_ALL, 0, NULL);
```
✅ This clears all allocated memory and exits the program.

---

## 💻 Example Usage
```c
#include "ft_safe_malloc.h"

int main(void)
{
    int *a = ft_safe_malloc(sizeof(int), ALLOCATE, 1, NULL);
    int *b = ft_safe_malloc(sizeof(int), ALLOCATE, 1, NULL);
    
    *a = 42;
    *b = 99;
    
    printf("a = %d, b = %d\n", *a, *b);
    
    ft_safe_malloc(0, FREE_ONE, 1, a); // Free only 'a'
    ft_safe_malloc(0, FREE_ALL, 0, NULL); // Free everything and exit
    
    return 0;
}
```

---

## 🏆 Why Use `ft_safe_malloc`?
- ✅ **Simplifies memory management** - No need to manually track allocations.
- ✅ **Prevents memory leaks** - Ensures all memory is properly freed.
- ✅ **Makes debugging easier** - Tracks and handles allocations safely.
- ✅ **Better safety** - Avoids use-after-free and double-free errors.

---

## 📜 License
This project is open-source. Feel free to use and modify it! 💡

📢 **Made by Hamza_hat**

