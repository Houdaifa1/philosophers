NAME = philo

FILES = creation_utils.c free_utils.c ft_atoi.c monitor_utils.c philosophers.c table_utils.c

CFLAGS = -Wall -Wextra -Werror # -fsanitize=thread -g3

all : $(NAME)

$(NAME) : $(FILES)
	cc $(CFLAGS) $(FILES) -o $(NAME)

clean :

fclean :
	rm -rf $(NAME)

re : fclean all
