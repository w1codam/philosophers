NAME = philosophers
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

SRC =	./src/main.c \
		./src/utility.c \
		./src/path.c \
		./src/clean.c \
		./src/error.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c

OBJ = ${SRC:%.c=%.o}

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re