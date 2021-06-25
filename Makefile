# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 13:25:40 by hyenam            #+#    #+#              #
#    Updated: 2021/06/25 15:22:02 by hyenam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC := gcc
RM = rm -rf
CFLAGS := -Wall -Wextra -Werror
INCLUDE = -I. -I./libft -I./gnl -I./mlx
LIBS = -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit
SRCS =	./util/key_hook.c ./util/key_move.c ./util/malloc_free.c ./util/set_dir.c ./util/utils.c \
		./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
		./map_parse/map_check.c ./map_parse/map_parse.c \
		./draw_map/draw_texture.c ./draw_map/draw_wall.c ./draw_map/raycasting.c \
		set_game.c main.c  

OBJS = $(SRCS:.c=.o)

LIB_DIR = ./libft/
LIB_NAME = ft
LIB = $(LIB_DIR)lib$(LIB_NAME).a

MLX_DIR = ./mlx/
MLX_NAME = mlx
MLX				= libmlx.a

all : $(NAME)

$(NAME): $(MLX) $(OBJS)
		gcc $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDE) $(LIBS)

$(MLX):
		make -C $(MLX_DIR) all
		make -C $(LIB_DIR) all
clean:
	$(RM) $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIB_DIR) clean

fclean : clean
	$(RM) $(NAME) $(MLX)
	make -C $(LIB_DIR) fclean

re : fclean $(NAME)

.PHONY : all clean fclean re