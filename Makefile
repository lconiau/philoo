NAME	= philo

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -pthread -g3
SRC_PATH = src/
OBJ_PATH = obj/
HEAD	= includes/philo.h


COMMANDS_DIR	=	$(SRC_PATH)init.c \
					$(SRC_PATH)main.c \
					$(SRC_PATH)dead_philo.c \
					$(SRC_PATH)routine.c \
					$(SRC_PATH)ft_check_args.c \
					$(SRC_PATH)ft_utils_2.c \
					$(SRC_PATH)ft_utils.c \

SRCS	=	$(COMMANDS_DIR)

OBJ		= $(SRCS:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(NAME): $(OBJ) Makefile $(HEAD)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all clean