NAME 	= philo
CFLAGS 	= -Wall -Wextra -Werror

SRC 	= philo.c parse_numbers.c utils.c routine.c
OBJ 	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: all clean fclean re
.SECONDARY: $(OBJ)