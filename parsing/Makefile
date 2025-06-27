CC = cc
CFLAGS = -Wall -Wextra -Werror
<<<<<<< HEAD
NAME = parsing
LIBFT = ./libft/libft.a

SRCS = check_syntax_error.c cmd_utils.c edir_handler.c  env_utils.c extract_special.c free_utils.c ft_itoa_custom.c handle_redir.c  parse_input.c token.c tokenizer.c var_utils.c \
 cmd_builder.c  debug.c env_expand.c extract_quoted.c extract_word.c free_utils.c get_token_type.c  main.c parse.c parsing.c  str_utils.c tokenize.c utils_1.c
=======
NAME = parsing.a
LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRCS = free_utils.c token.c check_syntax_error.c cmd_builder.c cmd_utils.c debug.c \
       edir_handler.c env_expand.c env_utils.c extract_quoted.c extract_special.c \
       extract_word.c ft_itoa_custom.c get_token_type.c handle_redir.c \
       parse_input.c parse.c parsing.c str_utils.c tokenize.c tokenizer.c \
       utils_1.c var_utils.c
>>>>>>> 98eec0c (version 1)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
