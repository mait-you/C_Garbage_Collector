# 🛠️ ft_safe_malloc - A Simple Garbage Collector in C

## 📌 Overview
`ft_safe_malloc` is a custom memory allocator that acts as a **garbage collector** for C programs. It helps in **tracking and managing memory allocations** to prevent memory leaks and **automatically free memory when needed**. 🚀

## 🔥 Features
✅ **Automatic memory tracking** - Keeps track of all allocated memory.  
✅ **Safe allocation** - If allocation fails, it automatically frees all memory and exits.  
✅ **Free one or all allocations** - You can free a specific allocation or clear everything.  
✅ **Free even untracked memory** - If you pass an untracked pointer, it will still be freed safely.  
✅ **Prevents memory leaks** - Ensures proper memory management.

---

## 📜 How It Works
The function `ft_safe_malloc` operates based on a **key system**:

| Key           | Macro Name   | Description                          |
|---------------|--------------|--------------------------------------|
| `1`           | `ALLOCATE`   | Allocate memory and track it         |
| `0`           | `FREE_ALL`   | Free all tracked memory and exit     |
| `2`           | `FREE_ONE`   | Free a specific memory block (even if untracked!) |

===========================================================================================
---

## 📌 Prototype
```c
void *ft_safe_malloc(size_t size, int key, int exit_status, void *to_delete);
```
### 🔍 Explanation of Parameters:
- **size**: The number of bytes to allocate (ignored for `FREE_ONE` and `FREE_ALL`).
- **key**: Determines the operation (`ALLOCATE`, `FREE_ONE`, or `FREE_ALL`).
- **exit_status**: Used when `FREE_ALL` is called to specify the exit status.
- **to_delete**: The pointer to free when `FREE_ONE` is used.

---

## 🏗️ Usage

### 🚀 Allocating Memory
```c
int *ptr = (int *)ft_safe_malloc(sizeof(int), ALLOCATE, 0, NULL);
```

### 🗑️ Freeing a Specific Pointer (Tracked or Untracked)
```c
ft_safe_malloc(0, FREE_ONE, 0, ptr);
```

### 💥 Freeing All Allocations
```c
ft_safe_malloc(0, FREE_ALL, 0, NULL);
```

---

## 💻 Example Usage
```c
int *a = ft_safe_malloc(sizeof(int), ALLOCATE, 0, NULL);
int *b = malloc(sizeof(int));

*a = 10; *b = 99;

ft_safe_malloc(0, FREE_ONE, 0, a);   // tracked
ft_safe_malloc(0, FREE_ONE, 0, b);   // untracked

ft_safe_malloc(0, FREE_ALL, 0, NULL);
```

---

## 🏆 Why Use `ft_safe_malloc`?
✅ **Simplifies memory management** - No need to manually track allocations  
✅ **Prevents memory leaks** - Ensures all memory is properly freed  
✅ **Makes debugging easier** - Tracks and handles allocations safely  
✅ **Safely handles untracked memory** - Frees anything without crashing  
✅ **Avoids double-free** errors and use-after-free bugs

---

## 🙌 Contribute or Contact
Feel free to **clone this project**, **test it**, and even try to break it! 😄  
If you find anything incorrect or have an idea for improvement, **don't hesitate to contact me** or submit a pull request! 🚀

---

## 📜 License
This project is open-source. Feel free to use and modify it! 💡

📢 **Made by Hamza_hat**


