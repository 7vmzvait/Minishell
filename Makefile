GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

CC = cc
CFLAGS =  -g -Wall -Wextra -Werror
#SAN =  -g -O0 -fno-omit-frame-pointer -fsanitize=address
SRC_DIR = src
BUILTINS = $(SRC_DIR)/builtins
EXEC_DIR = $(SRC_DIR)/exec
LIBFT_DIR = libft
EXPORT_DIR = $(BUILTINS)/export
PARSE_DIR = parsing
NAME = minishell
LIBS = -lreadline
LIBFT_LIB = $(LIBFT_DIR)/libft.a
PARSE_LIB = $(PARSE_DIR)/parsing.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(EXEC_DIR)/utils1.c \
	$(EXEC_DIR)/utils2.c \
	$(EXEC_DIR)/exec.c \
	$(EXEC_DIR)/handle_redir.c \
	$(EXEC_DIR)/redir.c \
	$(BUILTINS)/echo.c \
	$(BUILTINS)/cd.c \
	$(BUILTINS)/exit.c \
	$(BUILTINS)/env.c \
	$(BUILTINS)/pwd.c \
	$(BUILTINS)/unset.c \
	$(EXPORT_DIR)/export.c \
	$(EXPORT_DIR)/tools1.c \
	$(EXPORT_DIR)/tools2.c \
	$(EXPORT_DIR)/tools3.c \
	$(EXPORT_DIR)/tools4.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_LIB) $(PARSE_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(PARSE_LIB):
	@make -C $(PARSE_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(PARSE_LIB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PARSE_LIB) $(LIBFT_LIB) $(LIBS)
	@rm -f $(OBJS)
	@echo "$(GREEN)Build successful! $(NAME) is ready.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PARSE_DIR) clean
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean:	clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PARSE_DIR) fclean
	@echo "$(RED)Cleaned everything.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
