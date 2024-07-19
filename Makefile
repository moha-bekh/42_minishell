PROJECT =						minishell
NAME =							minishell

CC =							cc
CFLAGS =						-Wall -Wextra -Werror -g3
DEPFLAGS =						-MMD -MP
# -Wall -Wextra -Werror

FLAGS =							$(CFLAGS) $(DEPFLAGS)

INC_MINISHELL =					-I include
INC_LIBFT =						-I libft/include
INC_READLINE =					-I /usr/local/include
# INC_READLINE =				-I /usr/include/readline // home

INCLUDES =						$(INC_MINISHELL) $(INC_LIBFT) $(INC_READLINE)

LIBFT =							-L ./libft -l ft
READLINE =						-L /usr/local/lib -l readline
# READLINE =					-L /usr/lib/x86_64-linux-gnu -l readline // home

LIBRARYS =						$(LIBFT) $(READLINE)

DATA_STRUCT_DIR := 				data_struct/
DATA_STRUCT_SRCS := 			_env_clear\
								_env_pop_back\
								_env_pop_in\
								_env_print\
								_env_push_back\
								_env_push_in\
								_scp_clear\
								_scp_pop_back\
								_scp_print\
								_scp_push_back\
								_tok_clear\
								_tok_pop_back\
								_tok_print\
								_tok_push_back\

DATA_STRUCT_OBJS := 			$(addprefix $(DATA_STRUCT_DIR), $(addsuffix .o, $(DATA_STRUCT_SRCS)))

DATA_DIR := 					data/
DATA_SRCS := 					_data_init _data_cleaner
DATA_OBJS := 					$(addprefix $(DATA_DIR), $(addsuffix .o, $(DATA_SRCS)))

UTILS_DIR := 					utils/
UTILS_SRCS := 					_alloc _clean
UTILS_OBJS := 					$(addprefix $(UTILS_DIR), $(addsuffix .o, $(UTILS_SRCS)))

# TOKEN_DIR := 					token/
# TOKEN_SRCS := 					
# TOKEN_OBJS := 					$(addprefix $(TOKEN_DIR), $(addsuffix .o, $(TOKEN_SRCS)))

# EXPAND_DIR := 					expand/
# EXPAND_SRCS := 					
# EXPAND_OBJS := 					$(addprefix $(EXPAND_DIR), $(addsuffix .o, $(EXPAND_SRCS)))

# BULTINS_DIR = 					built_in/
# BULTINS_SRCS = 					
# BULTINS_OBJS = 					$(addprefix $(BULTINS_DIR), $(addsuffix .o, $(BULTINS_SRCS)))

SRC_DIR =						./src/
OBJ_DIR =						./obj/
FILES =							main

SRCS +=							$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(DATA_STRUCT_DIR), $(addsuffix .c, $(DATA_STRUCT_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(DATA_DIR), $(addsuffix .c, $(DATA_SRCS))))
SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(UTILS_DIR), $(addsuffix .c, $(UTILS_SRCS))))
# SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(TOKEN_DIR), $(addsuffix .c, $(TOKEN_SRCS))))
# SRCS +=							$(addprefix $(SRC_DIR), $(addprefix $(BULTINS_DIR), $(addsuffix .c, $(BULTINS_SRCS))))
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