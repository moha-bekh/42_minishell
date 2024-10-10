PROJECT =				minishell
NAME =					minishell

CC =					cc
CFLAGS =				-Wall -Wextra -g3
# CFLAGS =				-Wall -Wextra -Werror -g3
DEPFLAGS =				-MMD -MP

FLAGS =					$(CFLAGS) $(DEPFLAGS)

INC_MINISHELL =			-I include
INC_LIBFT =				-I libft/include
INC_READLINE =			-I /usr/local/include

INCLUDES =				$(INC_MINISHELL) $(INC_LIBFT) $(INC_READLINE)

LIBFT =					-L libft -l ft
READLINE =				-L /usr/local/lib -l readline

LIBRARYS =				$(LIBFT) $(READLINE)		

SRC_DIR			=		src/
OBJ_DIR			=		obj/
BULTIN_DIR		= 		built_in/
DATA_DIR		= 		data/
EXEC_DIR		= 		exec/
EXPAND_DIR		= 		expand/
SIG_DIR			= 		signal/
PARS_DIR		= 		parsing/
TOKEN_DIR		= 		token/
TREE_DIR		=		tree/
UTILS_DIR		= 		utils/

_SRC			:=		main

_DATA			:= 		_data_init\
						_env_init\
						_data_clear

_SIG			:=		_signal

_BULTIN		= 			_cd\
						_echo\
						_env\
						_exit\
						_export\
						_pwd\
						_unset

_TOKEN			:=		_op\
						_redir\
						_tok_list\
						_tok_proc\
						_tok_check

_TREE			:=		_tree_builder

_EXEC			:=		_exec\
						_redirs\

# _EXEC			:= 		_exec_process\
# 						_exec_proc\
# 						_exec_builtin\
# 						_redirs\

_EXPAND			:= 		_xpd\
						_xpd_str\
						_xpd_wildcards\
						_xpd_wildcards_utils\

_PARS			:= 		_parsing\
						_redirs

_UTILS			:= 		_bt_print\
						_dlst_print\
						_err_print\
						_get_data\
						_get_env_value\
						_get_rname\
						_is_builtin\
						_is_overflow\
						_is_varchr\
						_join_strings\
						_key_exist\
						_limit_quoted\
						_ltoa\
						_nb_lnargs\
						_path_slasher\
						_resolve_path\
						_tok_id\
						_varstr_conv\
						_wait_pids\
						_xpd_conv\
						_xpd_needed\

SRCS			+=		$(addprefix $(SRC_DIR), $(addsuffix .c, $(_SRC)))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(BULTIN_DIR), $(addsuffix .c, $(_BULTIN))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(DATA_DIR), $(addsuffix .c, $(_DATA))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(EXEC_DIR), $(addsuffix .c, $(_EXEC))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(EXPAND_DIR), $(addsuffix .c, $(_EXPAND))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(PARS_DIR), $(addsuffix .c, $(_PARS))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(SIG_DIR), $(addsuffix .c, $(_SIG))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(TOKEN_DIR), $(addsuffix .c, $(_TOKEN))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(TREE_DIR), $(addsuffix .c, $(_TREE))))
SRCS			+=		$(addprefix $(SRC_DIR), $(addprefix $(UTILS_DIR), $(addsuffix .c, $(_UTILS))))
OBJS = 					$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all:					$(NAME)
						@echo "$(GREEN)$(PROJECT) : All done!$(DEFAULT)"

$(OBJ_DIR)%.o:			$(SRC_DIR)%.c
						@mkdir -p $(@D)
						@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
						@echo "$(YELLOW)$(PROJECT) : $^ Compiling$(DEFAULT)"

$(NAME): $(OBJS)
						@make -sC ./libft
						@$(CC) $(FLAGS) $(OBJS) $(LIBRARYS) -o $(NAME)

clean:
						@rm -rf $(OBJ_DIR)
						@echo "$(CYAN)$(PROJECT) : Objs & Deps files cleaned!$(DEFAULT)"

fclean:					clean
						@make fclean -sC ./libft
						@rm -f $(NAME)
						@echo "$(PURPLE)$(PROJECT) : Content cleaned!$(DEFAULT)"

re:						fclean all
						@echo "$(PURPLE)$(PROJECT) : Clean and rebuilt everything!$(DEFAULT)"

norm:
						@clear
						@if ! norminette | grep "Error"; then echo "\033[32mOK!\033[0m"; fi

.PHONY:					all clean fclean re norm

-include $(DEP)

DEFAULT =				\033[0;39m
PURPLE =				\033[0;35m
GRAY =				 	\033[0;90m
RED =					\033[0;91m
GREEN =					\033[0;92m
YELLOW =				\033[0;93m
BLUE =					\033[0;94m
CYAN =					\033[0;96m
WHITE =				 	\033[0;97m