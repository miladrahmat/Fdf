NAME	= fdf

CFLAGS	= -Wextra -Wall -Werror

SRC_DIR = ./sources/

INC_DIR = ./includes/

LIBMLX	= $(INC_DIR)MLX42

HEADERS	= -I $(LIBMLX)/include/MLX42 -I $(INC_DIR)

LIBFT	= $(INC_DIR)libft/libft.a

LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw -lm

SRCS	= $(SRC_DIR)fdf.c \
			$(SRC_DIR)map_funcs.c \
			$(SRC_DIR)helper_funcs.c \
			$(SRC_DIR)helper_funcs1.c \
			$(SRC_DIR)line_algo.c \
			$(SRC_DIR)get_coordinates.c \
			$(SRC_DIR)hooks.c \
			$(SRC_DIR)color.c \
			$(SRC_DIR)scale.c \
			$(SRC_DIR)hook_funcs.c \
			$(SRC_DIR)rotate.c

OBJS	= ${SRCS:%.c=%.o}

all: libmlx $(NAME)

libmlx: .libmlx

.libmlx:
	@echo "\e[1;93m Compiling MLX42 ⏳ \e[0;37m"
	@cmake -S . $(LIBMLX) -B $(LIBMLX)/build > /dev/null || \
		echo "\e[1;31m Failed to compile MLX42 😔 \e[0;37m"; exit
	@make -s -C $(LIBMLX)/build -j4 > /dev/null
	@echo "\e[1;93m MLX42 compiled! 💪 \e[0;37m"
	@touch .libmlx

%.o: %.c
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME) && \
		echo "\e[1;92m FDF ready! Enjoy 🤩 \e[0;37m"

$(LIBFT):
	@echo "\e[1;93m Compiling Libft ⏳ \e[0;37m"
	@make -s -C $(INC_DIR)libft || \
		echo "\e[1;31m Failed to compile Libft 😔 \e[0;37m"; exit
	@echo "\e[1;93m Libft compiled! 💪 \e[0;37m"

clean:
	@make clean -s -C $(INC_DIR)libft && rm -rf $(OBJS) && \
		echo "\e[1;96m Removed all object files 🧹 \e[0;37m"

fclean: clean
	@make fclean -s -C $(INC_DIR)libft && rm -rf $(NAME) && \
		rm -f .libmlx && rm -rf $(LIBMLX)/build && \
		echo "\e[1;96m Removed all executables 🧹 \e[0;37m"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx