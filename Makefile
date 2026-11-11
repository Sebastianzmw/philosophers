# Makefile for push_swap.a

# Project name
NAME = philo
ARCHIVE = philo.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes -g -O2 
MAKE_LIB = ar -rcs

# Source files
SRCS = $(wildcard *.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(NAME)

$(NAME) : $(ARCHIVE)
	$(CC) $< -o $@

# Compile the library
$(ARCHIVE) : $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $^

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



# Clean object files
clean: 
	rm -f $(OBJS) $(ARCHIVE)

# Clean all generated files
fclean: clean
	rm -f $(NAME)


# Rebuild the project
re: fclean all

# Targets
.PHONY: all clean fclean re
