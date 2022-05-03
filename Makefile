### --- COLORS --- ###

RED		= '\033[31m'
GREEN	= '\033[1;32m'
YELLOW	= '\033[33m'
BLUE	= '\033[34m'
PURPLE	= '\033[1;35m'
CIAN	= '\033[36m'
WHITE	= '\033[37m'
NONE	= '\033[0m'

NAME = philo

SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/

SRCS = main.c atoi.c arguments_manage.c list_functions.c philos_functions.c \
		threads_functions.c actions.c time_functions.c

OBJS = $(SRCS:%.c=bin/%.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O0
RM = rm -f

###	--- RULES --- ###

all: $(NAME)

bin/%.o: src/%.c
	@mkdir -p bin
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo $(PURPLE)"[Creating philo]"$(NONE)
	@$(CC) -o $(NAME) $(OBJS) -pthread -fsanitize=address
	@echo $(GREEN)"$(NAME): ready to be executed"$(NONE)

clean:
	@$(RM) $(OBJS)
	@rm -rf bin/
	@echo $(RED)"[Object Files Deleted]"$(NONE)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED)"[Executable File Deleted]"$(NONE)

re: fclean $(NAME)

.PHONY: all clean fclean re
