NAME			=		minishell

NAME_B			=		minishell_bonus

HEADER_PATH		=		includes

HEADER_B_PATH	=		includes_bonus

LIBFT_PATH		=		libft

OBJECTS_PATH	=		objects

OBJECTS_B_PATH	=		objects_bonus

SOURCES_PATH	=		sources

SOURCES_B_PATH	=		sources_bonus

BUILT-IN_PATH	=		built-in

EXPORT_PATH		=		export

CD_PATH			=		cd

ENVP_PATH		=		envp_utils

ERROR_PATH		=		error_free

EXECUTION_PATH	=		execution

LEXER_PATH		=		lexer

LEXER_B_PATH	=		lexer_bonus

PARSER_PATH		=		parser

PARSER_B_PATH	=		parser_bonus

REDIRECT_PATH	=		redirect

SIGNAL_PATH		=		signal

TOKEN_PATH		=		token

WILDCARDS_PATH	=		wildcards_bonus

CD				=		$(addprefix $(CD_PATH)/,		cd_utils.c \
														cd.c)

EXPORT			=		$(addprefix $(EXPORT_PATH)/,	export_utils.c \
														export.c)

BUILT-IN		=		$(addprefix $(BUILT-IN_PATH)/,	$(CD) \
														$(EXPORT) \
														built-in_utils.c \
														echo.c \
														env.c \
														exit.c \
														pwd.c \
														unset.c)

ENVP			=		$(addprefix $(ENVP_PATH)/,		envp_utils.c)

ERROR			=		$(addprefix $(ERROR_PATH)/,		error_utils.c \
														free_utils.c)

EXECUTION		=		$(addprefix $(EXECUTION_PATH)/,	execution_command.c \
														execution_fd.c \
														execution_pathname.c \
														execution_utils.c \
														execution.c)

LEXER			=		$(addprefix $(LEXER_PATH)/,		lexer.c \
														quotes.c \
														spaces.c)

LEXER_B			=		$(addprefix $(LEXER_B_PATH)/,	quotes_bonus.c)

PARSER			=		$(addprefix $(PARSER_PATH)/,	parser_tilde_exp.c \
														parser_utils.c \
														parser_var_exp_utils.c \
														parser_var_exp.c \
														parser.c)

PARSER_B		=		$(addprefix $(PARSER_B_PATH)/,	parser_bonus.c)

REDIRECT		=		$(addprefix $(REDIRECT_PATH)/,	heredoc.c \
														redirect_utils.c \
														redirect.c)

SIGNAL			=		$(addprefix $(SIGNAL_PATH)/,	signal_handlers.c)

TOKEN			=		$(addprefix $(TOKEN_PATH)/,		token_utils.c)

WILDCARDS		=		$(addprefix $(WILDCARDS_PATH)/,	wildcards_bonus.c \
														wildcards_exp_aux_bonus.c \
														wildcards_exp_bonus.c \
														wildcards_exp_put_bonus.c \
														wildcards_list_utils_bonus.c \
														wildcards_utils_bonus.c)

LIBFT_H			=		$(addprefix $(LIBFT_PATH)/,		$(HEADER_PATH))

LIBFT			=		$(addprefix $(LIBFT_PATH)/,		libft.a)

SOURCES			=		minishell.c \
						$(BUILT-IN) \
						$(ENVP) \
						$(ERROR) \
						$(EXECUTION) \
						$(LEXER) \
						$(PARSER) \
						$(REDIRECT) \
						$(SIGNAL) \
						$(TOKEN)

SOURCES_B		=		$(LEXER_B) \
						$(PARSER_B) \
						$(WILDCARDS)

OBJECT			=		$(addprefix $(OBJECTS_PATH)/,	$(SOURCES:.c=.o))

SOURCE			=		$(addprefix $(SOURCES_PATH)/,	$(SOURCES))

OBJECT_B		=		$(filter-out $(OBJECTS_PATH)/$(LEXER_PATH)/quotes.o, \
							$(filter-out $(OBJECTS_PATH)/$(PARSER_PATH)/parser.o, $(OBJECT))) \
						$(addprefix $(OBJECTS_B_PATH)/,	$(SOURCES_B:.c=.o))

SOURCE_B		=		$(addprefix $(SOURCES_B_PATH)/,	$(SOURCES_B))

CC				=		cc

C_FLAGS			=		-Wall -Werror -Wextra -I$(HEADER_PATH) -I$(HEADER_B_PATH) -I$(LIBFT_H)

LIBFT_FLAGS		=		-L$(LIBFT_PATH) -lft

RM				=		rm -rf

all:					$(LIBFT) $(NAME)

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
						$(OBJECTS_PATH)/$(REDIRECT_PATH) \
						$(OBJECTS_PATH)/$(SIGNAL_PATH) \
						$(OBJECTS_PATH)/$(TOKEN_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/minishell.h
						@$(CC) $(C_FLAGS) -c $< -o $@

bonus:					$(LIBFT) $(OBJECTS_PATH) $(NAME_B)

$(NAME_B):				$(OBJECTS_B_PATH) $(OBJECT_B)
						@$(CC) $(C_FLAGS) $(OBJECT_B) $(LIBFT_FLAGS) -o $@ -lreadline

$(OBJECTS_B_PATH):
						@mkdir -p $(OBJECTS_B_PATH) \
						$(OBJECTS_B_PATH)/$(LEXER_B_PATH) \
						$(OBJECTS_B_PATH)/$(PARSER_B_PATH) \
						$(OBJECTS_B_PATH)/$(WILDCARDS_PATH)

$(OBJECTS_B_PATH)/%.o:	$(SOURCES_B_PATH)/%.c $(HEADER_B_PATH)/minishell_bonus.h
						@$(CC) $(C_FLAGS) -c $< -o $@

clean:
						@$(RM) $(OBJECTS_PATH) $(OBJECTS_B_PATH)
						@make -C $(LIBFT_PATH) clean

fclean:					clean
						@$(RM) $(NAME) $(NAME_B)
						@make -C $(LIBFT_PATH) fclean

re:						fclean all

.PHONY:					all bonus clean fclean re