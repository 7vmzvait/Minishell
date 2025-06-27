NAME = libft.a
CC   = cc
CFLAG = -Wall -Wextra -Werror

SRC	=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_isalpha.c ft_strcmp.c\
		ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
		ft_tolower.c ft_bzero.c   ft_isascii.c ft_substr.c ft_memcpy.c \
		ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
		ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c get_next_line.c\


SRC_BONUS =	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
	ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = $(SRC:.c=.o)
OBJB = $(SRC_BONUS:.c=.o)

$(NAME): $(OBJS)
	@ar csr  $(NAME) $(OBJS)

bonus: $(OBJB) $(OBJS)
	@ar csr  $(NAME) $(OBJB) $(OBJS)
%.o: %.c
	@$(CC) $(CFLAG) -c $<  -o $@
all: $(NAME) 
clean:
	@rm -f $(OBJS) $(OBJB)
fclean:clean
	@rm -f $(NAME)
re: fclean all
.PHONY: re clean all bonus fclean



