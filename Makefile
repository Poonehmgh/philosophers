NAME = philo
SRC_DIR = src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/ft_atoi.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
DEBUGF = -fsanitize=address

ifeq ($(DEBUG), 1)
FSAN = $(DEBUGF)
else
FSAN = 
endif

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(FSAN) $(SRC) -o $(NAME)
fclean: clean
	@rm -f $(NAME)
clean:
	@rm -f $(OBJ)
re: fclean all
.PHONY: all fclean clean re