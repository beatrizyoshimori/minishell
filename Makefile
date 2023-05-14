
NAME			=		minishell

LEXER_PATH		=		lexer

PARSER_PATH		=		parser

TOKEN_PATH		=		token

ENVP_PATH		=		envp_utils

EXIT_PATH		=		exit_free

BUILT-IN_PATH	=		built-in

EXPORT_PATH		=		export

LEXER			=		$(addprefix $(LEXER_PATH)/,		lexer.c \
														spaces.c \
														quotes.c)

PARSER			=		$(addprefix $(PARSER_PATH)/,	parser.c \
														parser_utils.c \
														parser_var_exp.c \
														parser_var_exp_utils.c)

TOKEN			=		$(addprefix $(TOKEN_PATH)/,		token_utils.c)

ENVP			=		$(addprefix $(ENVP_PATH)/,		envp_utils.c)

EXIT			=		$(addprefix $(EXIT_PATH)/,		exit_program.c \
														free_utils.c)

EXPORT			=		$(addprefix $(EXPORT_PATH)/,	export.c \
														export_utils.c)

BUILT-IN		=		$(addprefix $(BUILT-IN_PATH)/,	echo.c \
														exit.c \
														pwd.c \
														env.c \
														$(EXPORT))

SOURCES			=		minishell.c \
						$(LEXER) \
						$(PARSER) \
						$(TOKEN) \
						$(ENVP) \
						$(EXIT) \
						$(BUILT-IN)

SOURCES_PATH	=		sources

SOURCE			=		$(addprefix $(SOURCES_PATH)/, $(SOURCES))

OBJECTS_PATH	=		objects

OBJECTS			=		$(addprefix $(OBJECTS_PATH)/, $(SOURCES:.c=.o))

HEADER_PATH		=		includes

CC				=		cc

C_FLAGS			=		-Wall -Werror -Wextra -g3 -I$(HEADER_PATH) -I$(LIBFT_H)

LIBFT_PATH		=		libft

LIBFT_H			=		$(addprefix $(LIBFT_PATH)/, $(HEADER_PATH))

LIBFT			=		$(addprefix $(LIBFT_PATH)/, libft.a)

LIBFT_FLAGS		=		-L$(LIBFT_PATH) -lft

RM				=		rm -rf

all:					$(LIBFT) $(NAME)
						@./$(NAME)

$(LIBFT):
						@make -C $(LIBFT_PATH)

$(NAME):				$(OBJECTS_PATH) $(OBJECTS)
						@$(CC) $(C_FLAGS) $(OBJECTS) $(LIBFT_FLAGS) -o $@ -lreadline

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH) \
						$(OBJECTS_PATH)/$(LEXER_PATH) \
						$(OBJECTS_PATH)/$(PARSER_PATH) \
						$(OBJECTS_PATH)/$(TOKEN_PATH) \
						$(OBJECTS_PATH)/$(ENVP_PATH) \
						$(OBJECTS_PATH)/$(EXIT_PATH) \
						$(OBJECTS_PATH)/$(BUILT-IN_PATH) \
						$(OBJECTS_PATH)/$(BUILT-IN_PATH)/$(EXPORT_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/minishell.h
						@$(CC) $(C_FLAGS) -c $< -o $@

v:						$(LIBFT) $(NAME)
						@valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes \
						--suppressions=ignorelibs.txt --track-fds=yes --track-origins=yes \
						--trace-children-skip='/bin/,/sbin/' \
						./minishell

clean:
						@$(RM) $(OBJECTS_PATH)
						@make -C $(LIBFT_PATH) clean

fclean:					clean
						@$(RM) $(NAME)
						@make -C $(LIBFT_PATH) fclean

re:						fclean all

.PHONY:					all clean fclean re