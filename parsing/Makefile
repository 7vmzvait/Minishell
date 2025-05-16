CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS =  utils_2.c\
	ultis_1.c\

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_LIB)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJS) :$(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB)
clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean:clean
	@make -C $(LIBFT_DIR) fclean
re: fclean all
.PHONY: all clean fclean re

