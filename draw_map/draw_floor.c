/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:07:02 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/12 16:19:15 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	floor_cell(t_game *info)
{
	t_floor_info	floor;
	int				y;
	int				p;

	y = -1;
	while (++y < info->h / 2)
	{
		floor.ray_dirx0 = info->dirx - info->planex;
		floor.ray_diry0 = info->diry - info->planey;
		floor.ray_dirx1 = info->dirx + info->planex;
		floor.ray_diry1 = info->diry + info->planey;
		p = y - info->h / 2;
		floor.posz = 0.5 * info->h;
		floor.row_distance = floor.posz / p;
		floor.floor_stepx = floor.row_distance *
			(floor.ray_dirx1 - floor.ray_dirx0) / info->w;
		floor.floor_stepy = floor.row_distance *
			(floor.ray_diry1 - floor.ray_diry0) / info->w;
		floor.floorx = info->posx + floor.row_distance * floor.ray_dirx0;
		floor.floory = info->posy + floor.row_distance * floor.ray_diry0;
		draw_floor(info, &floor, y);
	}
}

void	draw_floor(t_game *info, t_floor_info *floor, int y)
{
	int x;
	int color;

	x = 0;
	while (++x < info->w)
	{
		floor->cellx = (int)(floor->floorx);
		floor->celly = (int)(floor->floory);
		floor->tx = (int)(TEXWIDTH * (floor->floorx -
			floor->cellx)) & (TEXWIDTH - 1);
		floor->ty = (int)(TEXHEIGHT * (floor->floory -
			floor->celly)) & (TEXHEIGHT - 1);
		floor->floorx += floor->floor_stepx;
		floor->floory += floor->floor_stepy;
		color = info->img.floor;
		info->buf[y][x] = color;
		color = info->img.cell;
		info->buf[info->h - y - 1][x] = color;
	}
}
