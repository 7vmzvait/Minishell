NAME    = test
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Ilibft
SRCS = \
	main.c \
	utils_1.c utils_2.c utils_3.c utils_4.c \
	utils_5.c utils_6.c utils_7.c utils_8.c \
	utils_9.c utils_10.c utils_11.c utils_12.c \
	utils_13.c utils_14.c \
	free_cmds.c free_tokens.c \
	ft_strcmp.c \
	handle_redir.c \
	syntax_error.c \
	toknize_input.c \
	useful_functions.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
