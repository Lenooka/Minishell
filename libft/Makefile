NAME            = libft.a
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -I.
RM              = rm -rf

SRCS            = ft_printerr_chars.c ft_printerr_up.c ft_printerrf_nmbr.c ft_printerr.c ft_strcmp.c ft_isalpha.c \
                  ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
                  ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c \
                  ft_memcmp.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c \
                  ft_split.c ft_itoa.c ft_strdup.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
                  ft_putendl_fd.c ft_putnbr_fd.c ft_printf_chars.c ft_printf_nmbr.c ft_printf_up.c ft_printf.c

BONUS_SRCS      = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
                  ft_lstnew.c ft_lstsize.c

OBJ_DIR         = objs
OBJS            = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS      = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

all:            $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):        $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus:          $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	$(RM) $(OBJ_DIR)

fclean:         clean
	$(RM) $(NAME)

re:             fclean all

.PHONY:         all clean fclean re bonus
