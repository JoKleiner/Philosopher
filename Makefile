
NAME            = philo
CC              = cc
CFLAGS          = -Wextra -Wall -Werror -pthread -g

SRC_DIR         = src
OBJ_DIR         = $(SRC_DIR)/obj
HEADER          = $(SRC_DIR)/philo.h

SRCS      		= philo.c monitor.c philo_thread.c thread_end.c list.c utils.c utils_write.c

OBJS            = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	@printf "Objects \033[0;32mcreated\033[0m\n"
	@printf "Linking \033[0;32m$(NAME)\033[0m\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 
	@printf "\033[0;32mphilo successfully built!\033[0m\n"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		printf "Remove o-files... "; \
		rm -rf $(OBJ_DIR); \
		printf "\033[0;31mRemoved.\033[0m\n"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		printf "Remove $(NAME)... "; \
		rm -f $(NAME); \
		printf "\033[0;31mRemoved.\033[0m\n"; \
	fi

re: fclean all
