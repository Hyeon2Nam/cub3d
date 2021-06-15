# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 13:25:40 by hyenam            #+#    #+#              #
#    Updated: 2021/06/15 11:51:28 by hyenam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC := gcc
RM = rm -rf
CFLAGS := -Wall -Wextra -Werror
INCLUDE = -I. -I./libft -I./gnl -I./mlx
LIBS = -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit

UTILS_DIR = ./util/
UTILS_NAME = key_hook.c \
		key_move.c \
		malloc_free.c \
		set_dir.c \
		utils.c

PARSE_DIR = ./map_parse/
PARSE_NAME = map_check.c \
				map_parse.c

MAP_DIR = ./draw_map/
MAP_NAME = draw_floor.c \
			draw_texture.c \
			draw_wall.c \
			raycasting.c

GNL_DIR = ./gnl/
GNL_NAME = get_next_line.c \
			get_next_line_utils.c

SRCS =	./util/key_hook.c ./util/key_move.c ./util/malloc_free.c ./util/set_dir.c ./util/utils.c \
		./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
		./map_parse/map_check.c ./map_parse/map_parse.c \
		./draw_map/draw_floor.c ./draw_map/draw_texture.c ./draw_map/draw_wall.c ./draw_map/raycasting.c \
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