PROJECT				=		libft

CC					=		cc
CFLAGS				=		-Wall -Werror -Wextra -I include -g3
DEPFLAGS			=		-MMD -MP
AR					=		ar -crs

FTIS_DIR			:=		ft_is/
FTIS				:=		ft_isalnum ft_isalpha ft_isascii ft_isdigit\
							ft_isprint ft_isspace\
							m_ishex_alpha m_ishexALPHA

FTMEM_DIR			:=		ft_mem/
FTMEM				:=		ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove\
							ft_memcpy ft_memset ft_memswap

FTPUT_DIR			:=		ft_put/
FTPUT				:=		ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTTO_DIR			:=		ft_to/
FTTO				:=		ft_atoi ft_atol ft_itoa ft_tolower ft_toupper ft_swap\
							m_atoi_base

FTSTR_DIR			:=		ft_str/
FTSTR				:=		ft_split ft_strchr ft_strcmp ft_strdup ft_striteri ft_strjoin \
							ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
							ft_strnstr ft_strrchr ft_strtrim ft_substr

FTLST_DIR			:=		ft_lst/
FTLST				:=		ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
							ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize\
							lst_clear lst_push_top lst_push_bot lst_pop_top\
							lst_last_prev

FT_PRINTF_DIR		:=		ft_printf/
FT_PRINTF			:=		ft_printf ft_print_char ft_print_hex ft_print_nbr \
							ft_print_ptr ft_print_str ft_print_unsigned ft_putchar \
							ft_putstr

M_PRINTF_DIR		:=		m_printf/
M_PRINTF			:=		m_printfd m_print_unsigned m_print_hex\

GNL_DIR				:=		get_next_line/
GNL					:=		get_next_line get_next_line_utils

# DLL_DIR				:=		dll/
# DLL					:=		dll_bot_pop dll_bot_push dll_bot_value dll_clear\
# 							dll_create dll_empty dll_new dll_print dll_size\
# 							dll_top_pop dll_top_push dll_top_value\
# 							node_create node_empty node_new\

BTREE_DIR			:=		btree/
BTREE				:=		btree_create btree_clear btree_join btree_print\
							btree_size

FREE_DIR			:=		m_free/
FREE				:=		m_free m_free_arr m_free_arrr m_free_tab

SORT_DIR			:=		sort/
SORT				:=		quick_sort\

SRC_FILES			+=		$(addprefix $(FTIS_DIR),$(FTIS))
SRC_FILES			+=		$(addprefix $(FTMEM_DIR),$(FTMEM))
SRC_FILES			+=		$(addprefix $(FTPUT_DIR),$(FTPUT))
SRC_FILES			+=		$(addprefix $(FTTO_DIR),$(FTTO))
SRC_FILES			+=		$(addprefix $(FTSTR_DIR),$(FTSTR))
SRC_FILES			+=		$(addprefix $(FTLST_DIR),$(FTLST))
SRC_FILES			+=		$(addprefix $(FT_PRINTF_DIR),$(FT_PRINTF))
SRC_FILES			+=		$(addprefix $(M_PRINTF_DIR),$(M_PRINTF))
SRC_FILES			+=		$(addprefix $(GNL_DIR),$(GNL))
# SRC_FILES			+=		$(addprefix $(DLL_DIR),$(DLL))
SRC_FILES			+=		$(addprefix $(BTREE_DIR),$(BTREE))
SRC_FILES			+=		$(addprefix $(FREE_DIR),$(FREE))
SRC_FILES			+=		$(addprefix $(SORT_DIR),$(SORT))

SRC_DIR 			=		src/
OBJ_DIR				=		obj/
TREE				=		.cache_exists

SRC 				= 		$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 				= 		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEP 				:=		$(patsubst %.o, %.d, $(OBJ))

NAME				=		libft.a

all					:		$(NAME)
							@echo "$(GREEN)$(PROJECT) : All done!$(DEFAULT)"

$(NAME)				:		$(OBJ)
							@$(AR) $@ $^
							@echo "$(GREEN)$(PROJECT) : Archive created!$(DEFAULT)"

$(OBJ_DIR)%.o 		: 		$(SRC_DIR)%.c | $(TREE)
							@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
# @echo "$(YELLOW)$(PROJECT) : $< $(DEFAULT)"

$(TREE)				:
							@mkdir -p $(OBJ_DIR)
							@mkdir -p $(OBJ_DIR)$(FTIS_DIR)
							@mkdir -p $(OBJ_DIR)$(FTMEM_DIR)
							@mkdir -p $(OBJ_DIR)$(FTPUT_DIR)
							@mkdir -p $(OBJ_DIR)$(FTTO_DIR)
							@mkdir -p $(OBJ_DIR)$(FTSTR_DIR)
							@mkdir -p $(OBJ_DIR)$(FTLST_DIR)
							@mkdir -p $(OBJ_DIR)$(FT_PRINTF_DIR)
							@mkdir -p $(OBJ_DIR)$(M_PRINTF_DIR)
							@mkdir -p $(OBJ_DIR)$(GNL_DIR)
							@mkdir -p $(OBJ_DIR)$(BTREE_DIR)
							@mkdir -p $(OBJ_DIR)$(FREE_DIR)
							@mkdir -p $(OBJ_DIR)$(SORT_DIR)
# @mkdir -p $(OBJ_DIR)$(DLL_DIR)

clean				:
							@rm -rf $(OBJ_DIR)
							@echo "$(CYAN)$(PROJECT) : Objs & Deps files cleaned!$(DEFAULT)"

fclean				:		clean
							@rm -rf $(NAME)
							@echo "$(PURPLE)$(PROJECT) : Content cleaned!$(DEFAULT)"

re					:		fclean all
							@echo "$(PURPLE)$(PROJECT) : Clean and rebuilt everything!$(DEFAULT)"

norm:
							@clear
							@if ! norminette | grep "Error"; then echo "\033[32mOK!\033[0m"; fi

.PHONY				:		all clean fclean re norm test

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