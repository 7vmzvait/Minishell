C = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src

SRC_B = $(SRC_DIR)/builtins
UTILS_DIR = utils
LIBFT_DIR = libft

NAME = minishell
LIBS = -lreadline
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(UTILS_DIR)/utils1.c \
	$(UTILS_DIR)/utils2.c \
	$(SRC_DIR)/executor.c \
	$(SRC_B)/echo.c \
	$(SRC_B)/cd.c \
	$(SRC_B)/exit.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
