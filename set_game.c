/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:42:16 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/14 11:39:58 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(t_game *info)
{
	info->w = 640;
	info->h = 480;
	info_init(info);
	set_buf_and_tex(info);
	load_texture(info);
	info->win = mlx_new_window(info->mlx, info->w, info->h, "Raycasterc");
	info->img.img = mlx_new_image(info->mlx, info->w, info->h);
	info->img.data = (int *)mlx_get_data_addr(info->img.img,
		&info->img.bpp, &info->img.size_l, &info->img.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, KEYPRESS, 0, &key_press, info);
	mlx_hook(info->win, KEYRELEASE, 0, &key_release, info);
	mlx_hook(info->win, KEYEXIT, 0, &key_exit, info);
	mlx_loop(info->mlx);
}

int		main_loop(t_game *info)
{
	raycasting(info);
	draw(info);
	key_update(info);
	return (0);
}
