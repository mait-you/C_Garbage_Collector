# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 16:30:00 by mait-you          #+#    #+#              #
#    Updated: 2025/04/19 16:07:51 by mait-you         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = libft_alloc_safety.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRC_FILES = ft_alloc_safety.c \
            ft_alloc_safety_action.c \
            ft_alloc_safety_utils.c \
            memory_fencing.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Header files
INCLUDES = -I.

# Default target
all: $(NAME)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create library archive
$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)
	@echo "Library $(NAME) compiled successfully"

# Compile with memory fencing enabled
fencing: clean
	$(CC) $(CFLAGS) $(INCLUDES) -DMEMEORY_FENCING=true -c $(SRC_FILES)
	ar rcs $(NAME) $(OBJ_FILES)
	@echo "Library $(NAME) compiled with memory fencing enabled"

# Clean object files
clean:
	rm -f $(OBJ_FILES)
	@echo "Object files cleaned"

# Clean object files and library
fclean: clean
	rm -f $(NAME)
	@echo "Library cleaned"

# Rebuild everything
re: fclean all

# Test target - create a simple test program
test: $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) test.c -L. -lft_alloc_safety -o test_alloc
	@echo "Test program compiled"

# Test with memory fencing enabled
test_fencing: fencing
	$(CC) $(CFLAGS) $(INCLUDES) -DMEMEORY_FENCING=true test.c -L. -lft_alloc_safety -o test_alloc_fencing
	@echo "Test program with memory fencing compiled"

# Phony targets
.PHONY: all clean fclean re fencing test test_fencing