NAME = tokenizer_test
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = free_cmds.c free_tokens.c handle_redir.c main.c syntax_error.c toknize_input.c ultis_1.c useful_functions.c utils_2.c \
utils_3.c utils_4.c utils_5.c utils_6.c utils_7.c utils_8.c utils_9.c utils_10.c utils_11.c utils_12.c utils_13.c utils_14.c ft_strcmp.c
OBJ = $(SRC:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
