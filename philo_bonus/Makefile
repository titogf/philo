
NAME = philo_bonus

SRC = main.c pthreads.c utils.c death.c

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
BLUE	= '\033[1;34m'
WHITE	= '\033[1;37m'

CC = gcc
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN)"Generating enforcible..."$(WHITE)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo $(GREEN)"$(NAME) Generated!"$(WHITE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo $(RED)"OBJS were deleted"$(WHITE)

fclean: clean
	rm -f $(NAME)
	@echo $(RED)"$(NAME) deleted"$(WHITE)

re: fclean all

n:
	"norminette"
