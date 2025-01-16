NAME 	= philo
CFLAGS 	= -Wall -Wextra -Werror -g3

SRC 	= 	philo_bonus.c check_args_bonus.c \
			utils_bonus.c routine_bonus.c routine_utils_bonus.c
OBJ 	= $(SRC:.c=.o)

all: bonus

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: all clean fclean re
.SECONDARY: $(OBJ)