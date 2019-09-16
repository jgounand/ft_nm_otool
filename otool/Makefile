NAME =			ft_otool


CC =			gcc

FLAGS =			-Wall -Werror -Wextra -g

HEADERS =		-I ./inc -I $(LIBFT_DIR)

LIBRARIES =		-L$(LIBFT_DIR) -l$(LIBFT_NAME)

LIBFT_NAME =	ft

LIBFT =			$(LIBFT_DIR)lib$(LIBFT_NAME).a

LIBFT_DIR =		./../libft/

SRC_DIR =		./src/

OBJ_DIR_NAME =	obj
OBJ_DIR =		./obj/

FILENAMES =	otool swap handle_64 handle_32 is_magic_swap check print handle_fat handle_ar


OBJ_PATHS :=	$(addsuffix .o,$(FILENAMES))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))

.PHONY: all clean fclean re libft

all: libft $(NAME)

$(NAME): $(LIBFT) $(OBJ_PATHS)
	@$(CC) $(OBJ_PATHS) $(HEADERS) $(LIBRARIES) -o $(NAME)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) created ✅\033[0m"

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c ./inc/ft_otool.h
	@/bin/mkdir -p $(OBJ_DIR)
	@echo -e "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m $<\c"
	@$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

libft:
	@Make -C ../libft/

$(LIBFT) ./libft/:
	@Make -C ../libft/

clean:
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m $(NAME)" 
	@/bin/rm -rf $(OBJ_DIR)
	@make -C ../libft/ clean
	@/usr/bin/find . -name "$(OBJ_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean:
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m $(NAME)" 
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) deleted ✅\033[0m"
	@Make fclean -C ../libft/
	@/bin/rm -f $(NAME)

re: fclean all
