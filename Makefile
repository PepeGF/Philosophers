
### --- COLORS --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
WHITE	= '\033[1;37m'
BLUE	= '\033[1;34m'

NAME = philo

SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/

SRCS = main.c atoi.c

OBJS = $(SRCS:%.c=bin/%.o)

CC = gcc
CFLAGS =-Wall -Werror -Wextra -g -O0
RM = rm -f

###		RULES		###

all: $(NAME)

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	echo $(PURPLE)"[Creating philo]"$(BLUE)
	$(CC) -o $(NAME) $(OBJS) #-fsanitize=address
	echo $(GREEN)"$(NAME): ready to be executed"$(WHITE)

clean:
	$(RM) $(OBJS)
	rm -rf bin/
	echo $(RED)"[Object Files Deleted]"$(WHITE)

fclean: clean
	$(RM) $(NAME)
	echo $(RED)"[Executable File Deleted]"$(WHITE)

re: fclean $(NAME)

.PHONY: all clean fclean re
