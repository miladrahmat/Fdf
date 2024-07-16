NAME	= fdf

CFLAGS	= -Wextra -Wall -Werror

SRC_DIR = ./sources/

INC_DIR = ./includes/

LIBMLX	= $(INC_DIR)MLX42

HEADERS	= -I $(LIBMLX)/include/MLX42 -I $(INC_DIR)

LIBFT	= $(INC_DIR)libft/libft.a

LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	= $(SRC_DIR)fdf.c \
			$(SRC_DIR)map_funcs.c \
			$(SRC_DIR)helper_funcs.c \
			$(SRC_DIR)line_algo.c \
			$(SRC_DIR)get_coordinates.c \
			$(SRC_DIR)hooks.c

OBJS	= ${SRCS:%.c=%.o}

all: libmlx $(NAME)

libmlx: .libmlx

.libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4
	@touch .libmlx

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME) && \
		echo "\e[1;32m fdf ready! Enjoy 🤩"

$(LIBFT):
	@make -C $(INC_DIR)libft && echo "\e[1;32m Libft compiled!"

clean:
	@make clean -C $(INC_DIR)libft && rm -rf $(OBJS) && \
		echo "\e[1;32m Removed all object files 🫡 \e[0;37m"

fclean: clean
	@make fclean -C $(INC_DIR)libft && rm -rf $(NAME) && \
		rm -f .libmlx && rm -rf $(LIBMLX)/build && \
		echo "\e[1;32m Removed all executables 🫡 \e[0;37m"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx