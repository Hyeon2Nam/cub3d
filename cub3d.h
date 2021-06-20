/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:21:33 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/20 13:48:40 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "key_macos.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

# define TEXWIDTH 64
# define TEXHEIGHT 64
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYEXIT 17

typedef struct	s_img
{
	void	*img;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		*data;
	int		width;
	int		height;
	int		size_l;
	int		endian;
	int		bpp;
	int		floor;
	int		ceiling;
}				t_img;

typedef struct	s_key
{
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_ar_l;
	int		key_ar_r;
	int		key_esc;
}				t_key;

typedef struct	s_map
{
	int		**map;
	int		w;
	int		h;
}				t_map;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_key	key;
	t_map	map_info;
	int		w;
	int		h;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	move_speed;
	double	rot_speed;
	int		**buf;
	int		*texture[4];
	int		tex_num;
	char	dir;
}				t_game;

typedef struct	s_floor_info
{
	float	row_distance;
	float	floor_stepx;
	float	floor_stepy;
	float	ray_dirx0;
	float	ray_diry0;
	float	ray_dirx1;
	float	ray_diry1;
	float	floorx;
	float	floory;
	float	posz;
	int		ceiling_texture;
	int		floor_texture;
	int		cellx;
	int		celly;
	int		tx;
	int		ty;
}				t_floor_info;

typedef struct	s_wall_info
{
	double	perp_wall_dist;
	double	delta_distx;
	double	delta_disty;
	double	side_distx;
	double	side_disty;
	double	ray_dirx;
	double	ray_diry;
	double	camera_x;
	double	tex_pos;
	double	wall_x;
	double	step;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		step_x;
	int		step_y;
	int		tex_x;
	int		tex_y;
	int		map_x;
	int		map_y;
	int		side;
	int		hit;
}				t_wall_info;

void			error_handler(char *text);

int				map_parse(int fd, t_game *map);
void			check_blank(char *buf, char **temp, int *blank);
int				check_option(t_game *map, char *buf);
int				set_tex_path(t_game *map, char *buf, int key);
int				set_color(t_game *map, char *buf, int key);

int				main_loop(t_game *info);
void			start_game(t_game *info);

int				map_check(t_game *map, char *str);
void			set_line_weight(char **temp, int h, int w);
void			map_atoi(t_game *map, char **temp_map);
int				is_correct(t_game *map, char **temp);
int				check_side(char **arr, int h);

void			raycasting(t_game *info);
void			dda(t_game *info, t_wall_info *wall_info);
void			calc_side_dist(t_game *info, t_wall_info *wall_info);
void			calc_prep_wall_dist(t_game *info, t_wall_info *wall_info);

void			floor_cell(t_game *info);
void			draw_floor(t_game *info, t_floor_info *floor, int y);

void			draw_wall(t_game *info, t_wall_info *wall_info, int x);
void			do_draw(t_game *info, t_wall_info *wall_info, int x);
void			calc_tex(t_wall_info *wall_info);
void			calc_line_height(t_game *info, t_wall_info *wall_info);

void			draw(t_game *info);
void			load_texture(t_game *info);
void			load_image(t_game *info, int *texture, char *path, t_img *img);

void			info_init(t_game *info);
int				set_buf_and_tex(t_game *info);
int				is_current_file(char *str, char *file);
int				data_checking(t_game *map, char data, int i, int j);

void			set_dir(t_game *map, char dir, int i, int j);
void			set_dir_ew(t_game *map, char dir);

char			**ft_char_malloc(int h, int w);
int				**ft_int_malloc(int h, int w);
void			ft_free(char **str);

int				key_press(int key, t_game *info);
int				key_release(int key, t_game *info);
int				key_exit(void);

void			key_update(t_game *info);
void			move_up_down(t_game **info);
void			move_left_right(t_game **info);
void			move_camera(t_game **info, double old_dirx, double old_planex);

#endif
