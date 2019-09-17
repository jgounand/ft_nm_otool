NAME =			ft_nm
NAME2 =			ft_otool


CC =			gcc

FLAGS =			-Wall -Werror -Wextra

HEADERS =		-I ./nm/inc -I $(LIBFT_DIR)
HEADERS2 =		-I ./otool//inc -I $(LIBFT_DIR)

LIBRARIES =		-L$(LIBFT_DIR) -l$(LIBFT_NAME)

LIBFT_NAME =	ft

LIBFT =			$(LIBFT_DIR)lib$(LIBFT_NAME).a

LIBFT_DIR =		./libft/

SRC_DIR =		./nm/src/
SRC_DIR2 =		./otool/src/

OBJ_DIR_NAME =	obj

OBJ_DIR =		./nm/obj/
OBJ_DIR2 =		./otool/obj/

FILENAMES =	nm get_type get_type_64 print swap handle_32 handle_64 handle_ar handle_fat is_magic_swap check tool is_magic_swap_tool swap_nlist

FILENAMES2 =	otool swap handle_64 handle_32 is_magic_swap check print handle_fat handle_ar

OBJ_PATHS :=	$(addsuffix .o,$(FILENAMES))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))

OBJ_PATHS2 :=	$(addsuffix .o,$(FILENAMES2))
OBJ_PATHS2 :=	$(addprefix $(OBJ_DIR2),$(OBJ_PATHS2))

.PHONY: all clean fclean re libft

all: libft $(NAME) $(NAME2)

$(LIBFT): ./libft/inc/libft.h
	@Make -C ./libft/

$(NAME): $(LIBFT) $(OBJ_PATHS)
	@$(CC) $(OBJ_PATHS) $(HEADERS) $(LIBRARIES) -o $(NAME)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) created ✅\033[0m"

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c ./nm/inc/ft_nm.h
	@/bin/mkdir -p $(OBJ_DIR)
	@echo -e "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m $<\c"
	@$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

$(NAME2): $(LIBFT) $(OBJ_PATHS2)
	@$(CC) $(OBJ_PATHS2) $(HEADERS2) $(LIBRARIES) -o $(NAME2)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME2) created ✅\033[0m"

$(OBJ_PATHS2): $(OBJ_DIR2)%.o: $(SRC_DIR2)%.c ./otool/inc/ft_otool.h
	@/bin/mkdir -p $(OBJ_DIR2)
	@echo -e "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m $<\c"
	@$(CC) -c $(FLAGS) $(HEADERS2) $< -o $@

clean:
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m $(NAME) and $(NAME2)" 
	@/bin/rm -rf $(OBJ_DIR) $(OBJ_DIR2)
	@make clean -C ./libft/
	@/usr/bin/find . -name "$(OBJ_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean:
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m $(NAME) and $(NAME2)" 
	@/bin/rm -rf $(OBJ_DIR) $(OBJ_DIR2)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) deleted ✅\033[0m"
	@Make fclean -C ./libft/
	@/bin/rm -f $(NAME) $(NAME2)

re: fclean all
