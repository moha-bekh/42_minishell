PROJECT		=		data_struct
CC			=		cc
CFLAGS		=		-Wall -Wextra -Werror -I include -g3
DEPFLAGS	=		-MMD -MP
AR			=		ar -crs

DLL_DIR		:=		dll/
DLL_SRCS	:=		_blc_dll_clear\
					_blc_dll_pop_back\
					_blc_dll_print\
					_blc_dll_push_back\
					_dll_clear\
					_dll_pop_back\
					_dll_pop_front\
					_dll_pop_in\
					_dll_print_env\
					_dll_print\
					_dll_push_back\
					_dll_push_front\
					_dll_push_in\
					_tok_dll_clear\
					_tok_dll_pop_back\
					_tok_dll_print\
					_tok_dll_push_back\
					_tok_dll_rev_childs\

BTREE_DIR	:=		btree/
BTREE_SRCS	:=		_blc_bt_clear\
					_blc_bt_create\
					_blc_bt_join\
					_blc_bt_size\
					_tok_bt_clear\
					_tok_bt_create\
					_tok_bt_join\
					_tok_bt_print\
					_tok_bt_push\
					_tok_bt_size\

GRAPH_DIR	:=		graph/
GRAPH_SRCS	:=		_graph_add_edge\
					_graph_clear\
					_graph_create\
					_graph_display\
					_graph_print\
					_node_add\

UTILS_DIR	:=		utils/
UTILS_SRCS	:=		_alloc\
					_clean\
					ft_memset\
					ft_putstr_fd\

SRC_FILES	+=		$(addprefix $(DLL_DIR), $(DLL_SRCS))
SRC_FILES	+=		$(addprefix $(BTREE_DIR), $(BTREE_SRCS))
SRC_FILES	+=		$(addprefix $(GRAPH_DIR), $(GRAPH_SRCS))
SRC_FILES	+=		$(addprefix $(UTILS_DIR), $(UTILS_SRCS))

SRC_DIR		=		src/
OBJ_DIR		=		obj/
TREE		=		.cache_exists

SRC			=		$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEP			:=		$(patsubst %.o, %.d, $(OBJ))

NAME		=		libdata_struct.a

all			:		$(NAME)
					@echo "$(GREEN)$(PROJECT) : All done!$(DEFAULT)"

x			:		
					@$(CC) $(CFLAGS) main.c -L . -l data_struct

$(NAME)		:		$(OBJ)
					@$(AR) $@ $^
					@echo "$(GREEN)$(PROJECT) : Process succed!$(DEFAULT)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(TREE)
					@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
					@echo "$(YELLOW)Compiling: $< $(DEFAULT)"

$(TREE)		:
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(DLL_DIR)
					@mkdir -p $(OBJ_DIR)$(BTREE_DIR)
					@mkdir -p $(OBJ_DIR)$(GRAPH_DIR)
					@mkdir -p $(OBJ_DIR)$(UTILS_DIR)

clean		:
					@rm -rf $(OBJ_DIR)
					@echo "$(GREEN)$(PROJECT) : Object files removed!$(DEFAULT)"

fclean		:		clean
					@rm -f $(NAME)
					@echo "$(GREEN)$(PROJECT) : $(NAME) removed!$(DEFAULT)"

re			:		fclean all
					@echo "$(GREEN)$(PROJECT) : $(NAME) recompiled!$(DEFAULT)"

.PHONY		:		all clean fclean re

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