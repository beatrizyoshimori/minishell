NAME			=		minishell

HEADER_PATH		=		includes

LIBFT_PATH		=		libft

OBJECTS_PATH	=		objects

SOURCES_PATH	=		sources

BUILT-IN_PATH	=		built-in

EXPORT_PATH		=		export

CD_PATH			=		cd

ENVP_PATH		=		envp_utils

ERROR_PATH		=		error_free

EXECUTION_PATH	=		execution

LEXER_PATH		=		lexer

PARSER_PATH		=		parser

SIGNAL_PATH		=		signal

TOKEN_PATH		=		token

CD				=		$(addprefix $(CD_PATH)/,		cd_utils.c \
														cd.c)

EXPORT			=		$(addprefix $(EXPORT_PATH)/,	export_utils.c \
														export.c)

BUILT-IN		=		$(addprefix $(BUILT-IN_PATH)/,	$(CD) \
														$(EXPORT) \
														echo.c \
														env.c \
														exit.c \
														pwd.c \
														unset.c \
														built-in_utils.c)

ENVP			=		$(addprefix $(ENVP_PATH)/,		envp_utils.c)

ERROR			=		$(addprefix $(ERROR_PATH)/,		error_utils.c \
														free_utils.c)

EXECUTION		=		$(addprefix $(EXECUTION_PATH)/,	execution.c \
														execution_fd.c \
														execution_command.c \
														execution_pathname.c \
														execution_utils.c)

LEXER			=		$(addprefix $(LEXER_PATH)/,		lexer.c \
														quotes.c \
														spaces.c)

PARSER			=		$(addprefix $(PARSER_PATH)/,	parser_tilde_exp.c \
														parser_utils.c \
														parser_var_exp_utils.c \
														parser_var_exp.c \
														parser.c \
														redirect.c \
														redirect_utils.c \
														heredoc.c)

SIGNAL			=		$(addprefix $(SIGNAL_PATH)/,	signal_handlers.c)

TOKEN			=		$(addprefix $(TOKEN_PATH)/,		token_utils.c)

LIBFT_H			=		$(addprefix $(LIBFT_PATH)/, $(HEADER_PATH))

LIBFT			=		$(addprefix $(LIBFT_PATH)/, libft.a)

SOURCES			=		non_ms_functions.c \
						minishell.c \
						$(BUILT-IN) \
						$(ENVP) \
						$(ERROR) \
						$(EXECUTION) \
						$(LEXER) \
						$(PARSER) \
						$(SIGNAL) \
						$(TOKEN)

OBJECT			=		$(addprefix $(OBJECTS_PATH)/, $(SOURCES:.c=.o))

SOURCE			=		$(addprefix $(SOURCES_PATH)/, $(SOURCES))

CC				=		cc

C_FLAGS			=		-Wall -Werror -Wextra -g3 -I$(HEADER_PATH) -I$(LIBFT_H)

LIBFT_FLAGS		=		-L$(LIBFT_PATH) -lft

RM				=		rm -rf

all:					$(LIBFT) $(NAME)
						@./$(NAME)

$(LIBFT):
						@make -C $(LIBFT_PATH)

$(NAME):				$(OBJECTS_PATH) $(OBJECT)
						@$(CC) $(C_FLAGS) $(OBJECT) $(LIBFT_FLAGS) -o $@ -lreadline

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH) \
						$(OBJECTS_PATH)/$(BUILT-IN_PATH) \
						$(OBJECTS_PATH)/$(BUILT-IN_PATH)/$(CD_PATH) \
						$(OBJECTS_PATH)/$(BUILT-IN_PATH)/$(EXPORT_PATH) \
						$(OBJECTS_PATH)/$(ENVP_PATH) \
						$(OBJECTS_PATH)/$(ERROR_PATH) \
						$(OBJECTS_PATH)/$(EXECUTION_PATH) \
						$(OBJECTS_PATH)/$(LEXER_PATH) \
						$(OBJECTS_PATH)/$(PARSER_PATH) \
						$(OBJECTS_PATH)/$(SIGNAL_PATH) \
						$(OBJECTS_PATH)/$(TOKEN_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/minishell.h
						@$(CC) $(C_FLAGS) -c $< -o $@

v:						$(LIBFT) $(NAME)
						@valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes \
						--suppressions=ignorelibs.txt --track-fds=yes --track-origins=yes \
						--trace-children-skip='*/bin/*,*/sbin/*' \
						./minishell

clean:
						@$(RM) $(OBJECTS_PATH)
						@make -C $(LIBFT_PATH) clean

fclean:					clean
						@$(RM) $(NAME)
						@make -C $(LIBFT_PATH) fclean

re:						fclean all

.PHONY:					all clean fclean re