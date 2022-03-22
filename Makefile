CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra

# -fsanitize=address

SRC = $(wildcard ./src/*.c ./utiles/*.c) 

NAME = philo

OBJ = $(SRC:.c=.o)

THREAD = -pthread

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(THREAD) $(SRC) -o $(NAME)

%.o : %.c
	$(CC) -c $(CFLAGS) $(THREAD) $(SRC) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

lauch: re
	@./philo

.PHONY: all clean fclean re