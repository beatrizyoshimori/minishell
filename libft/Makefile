NAME			=		libft.a

SOURCES			=		ft_isalpha.c \
						ft_isdigit.c \
						ft_isalnum.c \
						ft_isascii.c \
						ft_isprint.c \
						ft_iswhitespace.c \
						ft_strlen.c \
						ft_memset.c \
						ft_bzero.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_strlcpy.c \
						ft_strlcat.c \
						ft_toupper.c \
						ft_tolower.c \
						ft_strchr.c \
						ft_strrchr.c \
						ft_strncmp.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_strnstr.c \
						ft_atoi.c \
						ft_atoull.c \
						ft_calloc.c \
						ft_strdup.c \
						ft_substr.c \
						ft_strjoin.c \
						ft_strtrim.c \
						ft_split.c \
						ft_itoa.c \
						ft_strmapi.c \
						ft_striteri.c \
						ft_putchar_fd.c \
						ft_putstr_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c \
						ft_lstnew.c \
						ft_lstadd_front.c \
						ft_lstsize.c \
						ft_lstlast.c \
						ft_lstadd_back.c \
						ft_lstdelone.c \
						ft_lstclear.c \
						ft_lstiter.c \
						ft_lstmap.c

SOURCES_PATH	=		sources

SOURCE			=		$(addprefix $(SOURCES_PATH)/, $(SOURCES))

OBJECTS_PATH	=		objects

OBJECTS			=		$(addprefix $(OBJECTS_PATH)/, $(SOURCES:%.c=%.o))

HEADER_PATH		=		includes

CC				=		cc

C_FLAGS			=		-Wall -Werror -Wextra -g3 -I$(HEADER_PATH)

RM				=		rm -rf

all:					$(NAME)

$(NAME):				$(OBJECTS_PATH) $(OBJECTS)

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/libft.h
						@$(CC) $(C_FLAGS) -c $< -o $@
						@ar rcs $(NAME) $@

clean:
						@$(RM) $(OBJECTS_PATH)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re