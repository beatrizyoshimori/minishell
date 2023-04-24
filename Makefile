
NAME			=		minishell

SOURCES 		=		minishell.c

SOURCES_PATH	=		sources

SOURCE			=		$(addprefix $(SOURCES_PATH)/, $(SOURCES))

OBJECTS_PATH	=		objects

OBJECTS			=		$(addprefix $(OBJECTS_PATH)/, $(SOURCES:.c=.o))

HEADER_PATH		=		includes

CC				=		cc

C_FLAGS			=		-Wall -Wextra -Werror -g3 -I$(HEADER_PATH)

RM				=		rm -rf

all: 					$(NAME)

$(NAME):				$(OBJECTS_PATH) $(OBJECTS)
						$(CC) $(C_FLAGS) $(OBJECTS) -o $@

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/minishell.h
					 	$(CC) $(C_FLAGS) -c $< -o $@

clean:
						@$(RM) $(OBJECTS_PATH)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re