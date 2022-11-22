NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC =	./src/main.c \
		./src/utility.c \
		./src/log.c \
		./src/setup.c \
		./src/philosopher.c \
		./src/monitor.c \
		./src/threads.c \
		./src/protected_pthread.c

OBJ = ${SRC:%.c=%.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re