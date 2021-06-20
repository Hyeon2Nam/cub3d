/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:02:31 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/20 14:49:20 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raycasting(t_game *info)
{
	t_wall_info		wall_info;
	int				x;

	floor_ceiling(info);
	x = -1;
	while (++x < info->w)
	{
		wall_info.camera_x = 2 * x / (double)info->w - 1;
		wall_info.ray_dirx = info->dirx + info->planex * wall_info.camera_x;
		wall_info.ray_diry = info->diry + info->planey * wall_info.camera_x;
		wall_info.map_x = (int)info->posx;
		wall_info.map_y = (int)info->posy;
		wall_info.delta_distx = fabs(1 / wall_info.ray_dirx);
		wall_info.delta_disty = fabs(1 / wall_info.ray_diry);
		wall_info.hit = 0;
		calc_side_dist(info, &wall_info);
		dda(info, &wall_info);
		calc_prep_wall_dist(info, &wall_info);
		draw_wall(info, &wall_info, x);
	}
}

void	dda(t_game *info, t_wall_info *wall_info)
{
	while (wall_info->hit == 0)
	{
		if (wall_info->side_distx < wall_info->side_disty)
		{
			wall_info->side_distx += wall_info->delta_distx;
			wall_info->map_x += wall_info->step_x;
			wall_info->side = 0;
		}
		else
		{
			wall_info->side_disty += wall_info->delta_disty;
			wall_info->map_y += wall_info->step_y;
			wall_info->side = 1;
		}
		if (info->map_info.map[wall_info->map_x][wall_info->map_y] > 0)
			wall_info->hit = 1;
	}
}

void	calc_side_dist(t_game *info, t_wall_info *wall_info)
{
	if (wall_info->ray_dirx < 0)
	{
		wall_info->step_x = -1;
		wall_info->side_distx = (info->posx - wall_info->map_x) *
			wall_info->delta_distx;
	}
	else
	{
		wall_info->step_x = 1;
		wall_info->side_distx = (wall_info->map_x + 1.0 - info->posx) *
			wall_info->delta_distx;
	}
	if (wall_info->ray_diry < 0)
	{
		wall_info->step_y = -1;
		wall_info->side_disty = (info->posy - wall_info->map_y) *
			wall_info->delta_disty;
	}
	else
	{
		wall_info->step_y = 1;
		wall_info->side_disty = (wall_info->map_y + 1.0 - info->posy) *
			wall_info->delta_disty;
	}
}

void	calc_prep_wall_dist(t_game *info, t_wall_info *wall_info)
{
	if (wall_info->side == 0)
		wall_info->perp_wall_dist = (wall_info->map_x - info->posx +
			(1 - wall_info->step_x) / 2) / wall_info->ray_dirx;
	else
		wall_info->perp_wall_dist = (wall_info->map_y - info->posy +
			(1 - wall_info->step_y) / 2) / wall_info->ray_diry;
}

void	floor_ceiling(t_game *info)
{
	int	color;
	int	x;
	int	y;

	y = -1;
	while (++y < info->h / 2)
	{
		x = 0;
		while (++x < info->w)
		{
			color = info->img.ceiling;
			info->buf[y][x] = color;
			color = info->img.floor;
			info->buf[info->h - y - 1][x] = color;
		}
	}
}
