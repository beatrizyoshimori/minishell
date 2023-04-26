
NAME			=		minishell

SOURCES			=		minishell.c \
						list_utils.c

SOURCES_PATH	=		sources

SOURCE			=		$(addprefix $(SOURCES_PATH)/, $(SOURCES))

OBJECTS_PATH	=		objects

OBJECTS			=		$(addprefix $(OBJECTS_PATH)/, $(SOURCES:.c=.o))

HEADER_PATH		=		includes

CC				=		cc

C_FLAGS			=		-g3 -I$(HEADER_PATH) -I$(LIBFT_PATH)

LIBFT_FLAGS		=		-Llibft -lft

LIBFT_PATH		=		libft

LIBFT			=		$(addprefix $(LIBFT_PATH)/, libft.a)

RM				=		rm -rf

all:					$(LIBFT) $(NAME)

$(LIBFT):
						@make -C $(LIBFT_PATH)

$(NAME):				$(OBJECTS_PATH) $(OBJECTS)
						$(CC) $(C_FLAGS) $(OBJECTS) $(LIBFT_FLAGS) -o $@ -lreadline

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/minishell.h
					 	$(CC) $(C_FLAGS) -c $< -o $@

clean:
						@$(RM) $(OBJECTS_PATH)
						@make -C $(LIBFT_PATH) clean

fclean:					clean
						@$(RM) $(NAME)
						@make -C $(LIBFT_PATH) fclean

re:						fclean all

.PHONY:					all clean fclean re