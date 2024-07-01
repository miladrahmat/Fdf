NAME	:= Game
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= MLX42

HEADERS	:= -I $(LIBMLX)/include/MLX42
LIBFT	:= libft/libft.a
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= fdf.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -g $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

$(LIBFT):
	@make -C libft
clean:
	@make clean -C libft
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx