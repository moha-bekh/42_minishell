PROJECT =						minishell
NAME =							minishell

CC =							cc
CFLAGS =						-Wall -Wextra -Werror -g3
DEPFLAGS =						-MMD -MP

FLAGS =							$(CFLAGS) $(DEPFLAGS)

SRC_DIR =						./src/
OBJ_DIR =						./obj/

INC_MINISHELL =					-I include
INC_LIBFT =						-I libft/include
INC_READLINE =					-I /usr/local/include

INCLUDES =						$(INC_MINISHELL) $(INC_LIBFT) $(INC_READLINE)

LIBFT =							-L ./libft -l ft
READLINE =						-L /usr/local/lib -l readline

LIBRARYS =						$(LIBFT) $(READLINE)		

SRC_SRCS =							main

DLLST_DIR := 					_dlst/
DLLST_SRCS :=					\
								_cmd_pop\
								_cmd_push\
								_cmd_print\
								_dlst_push\
								_dlst_pop\
								_dlst_sort\
								_dlst_print\
								_dlst_utils

BTREE_DIR := 					_btree/
BTREE_SRCS :=					\
								_bt_clear\
								_bt_create\
								_bt_join\
								_bt_print\
								_bt_push_left\
								_bt_push_right\
								_bt_push_root

UTILS_DIR := 					utils/
UTILS_SRCS := 					\
								_utils_1\
								_utils_2

SIG_DIR := 						signal/
SIG_SRCS := 					\
								_signal

DATA_DIR := 					data/
DATA_SRCS := 					\
								_data_init\
								_data_clear

ENV_DIR	:= 						env/
ENV_SRCS :=						\
								_env

BULTINS_DIR = 					built_in/
BULTINS_SRCS = 					\
								_cd\
								_echo\
								_env\
								_exit\
								_export\
								_pwd\
								_unset

TOKEN_DIR := 					token/
TOKEN_SRCS :=					\
								_op\
								_redir\
								_token_list

# EXPAND_DIR := 					expand/
# EXPAND_SRCS := 				\
								_expand\
# 								_exp_str

PARS_DIR := 					parsing/
PARS_SRCS := 					\
								_parsing\
								_redirs

TREE_DIR :=						tree/
TREE_SRCS :=					\
								_tree_builder

EXEC_DIR := 					exec/
EXEC_SRCS := 					\
								_exec\
								_exec_child\
								_exec_builtin\
								_path


DLLST_OBJS :=					$(addprefix $(DLLST_DIR), $(addsuffix .o, $(DLLST_SRCS)))
OP_TREE_OBJS := 				$(addprefix $(OP_TREE_DIR), $(addsuffix .o, $(OP_TREE_SRCS)))
UTILS_OBJS := 					$(addprefix $(UTILS_DIR), $(addsuffix .o, $(UTILS_SRCS)))
SIG_OBJS := 					$(addprefix $(SIG_DIR), $(addsuffix .o, $(SIG_SRCS)))
DATA_OBJS := 					$(addprefix $(DATA_DIR), $(addsuffix .o, $(DATA_SRCS)))
ENV_OBJS := 					$(addprefix $(ENV_DIR), $(addsuffix .o, $(ENV_SRCS)))
BULTINS_OBJS = 					$(addprefix $(BULTINS_DIR), $(addsuffix .o, $(BULTINS_SRCS)))
TOKEN_OBJS := 					$(addprefix $(TOKEN_DIR), $(addsuffix .o, $(TOKEN_SRCS)))
# EXPAND_OBJS := 					$(addprefix $(EXPAND_DIR), $(addsuffix .o, $(EXPAND_SRCS)))
PARS_OBJS := 					$(addprefix $(PARS_DIR), $(addsuffix .o, $(PARS_SRCS)))
TREE_OBJS :=					$(addprefix $(TREE_DIR), $(addsuffix .o, $(TREE_SRCS)))
EXEC_OBJS := 					$(addprefix $(EXEC_DIR), $(addsuffix .o, $(EXEC_SRCS)))

SRCS +=							$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SRCS)))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(DLLST_DIR), $(addsuffix .c, $(DLLST_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(BTREE_DIR), $(addsuffix .c, $(BTREE_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(UTILS_DIR), $(addsuffix .c, $(UTILS_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(SIG_DIR), $(addsuffix .c, $(SIG_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(DATA_DIR), $(addsuffix .c, $(DATA_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(BULTINS_DIR), $(addsuffix .c, $(BULTINS_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(ENV_DIR), $(addsuffix .c, $(ENV_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(TOKEN_DIR), $(addsuffix .c, $(TOKEN_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(TREE_DIR), $(addsuffix .c, $(TREE_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(EXEC_DIR), $(addsuffix .c, $(EXEC_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(PARS_DIR), $(addsuffix .c, $(PARS_SRCS))))
# SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(EXPAND_DIR), $(addsuffix .c, $(EXPAND_SRCS))))
OBJS = 							$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all:							$(NAME)
								@echo "$(GREEN)$(PROJECT) : All done!$(DEFAULT)"

$(OBJ_DIR)%.o:					$(SRC_DIR)%.c
								@mkdir -p $(@D)
								@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
								@echo "$(YELLOW)$(PROJECT) : $^ Compiling$(DEFAULT)"

$(NAME): $(OBJS)
								@make -sC ./libft
								@$(CC) $(FLAGS) $(OBJS) $(LIBRARYS) -o $(NAME)

clean:
								@rm -rf $(OBJ_DIR)
								@echo "$(CYAN)$(PROJECT) : Objs & Deps files cleaned!$(DEFAULT)"

fclean:							clean
								@make fclean -sC ./libft
								@rm -f $(NAME)
								@echo "$(PURPLE)$(PROJECT) : Content cleaned!$(DEFAULT)"

re:								fclean all
								@echo "$(PURPLE)$(PROJECT) : Clean and rebuilt everything!$(DEFAULT)"

norm:
								@clear
								@if ! norminette | grep "Error"; then echo "\033[32mOK!\033[0m"; fi

.PHONY:							all clean fclean re norm

-include $(DEP)

DEFAULT				= 		\033[0;39m
PURPLE				=		\033[0;35m
GRAY				= 		\033[0;90m
RED					=		\033[0;91m
GREEN				=		\033[0;92m
YELLOW				=		\033[0;93m
BLUE				=		\033[0;94m
CYAN				=		\033[0;96m
WHITE				= 		\033[0;97m