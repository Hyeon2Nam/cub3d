/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:30:11 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/20 15:24:38 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_wall(t_game *info, t_wall_info *wall_info, int x)
{
	calc_line_height(info, wall_info);
	if (wall_info->side == 0)
		wall_info->wall_x = info->posy + wall_info->perp_wall_dist *
			wall_info->ray_diry;
	else
		wall_info->wall_x = info->posx + wall_info->perp_wall_dist *
			wall_info->ray_dirx;
	wall_info->wall_x -= floor(wall_info->wall_x);
	wall_info->tex_x = (int)(wall_info->wall_x * (double)TEXWIDTH);
	calc_tex(wall_info);
	wall_info->tex_pos = (wall_info->draw_start - info->h / 2 +
		wall_info->line_height / 2) * wall_info->step;
	do_draw(info, wall_info, x);
}

void	do_draw(t_game *info, t_wall_info *wall_info, int x)
{
	int y;
	int color;

	y = wall_info->draw_start - 1;
	while (++y < wall_info->draw_end)
	{
		wall_info->tex_y = (int)wall_info->tex_pos;
		wall_info->tex_pos += wall_info->step;
		if (wall_info->side == 0 && wall_info->ray_dirx > 0)
			color = info->texture[1]
				[TEXHEIGHT * wall_info->tex_y + wall_info->tex_x];
		if (wall_info->side == 0 && wall_info->ray_dirx < 0)
			color = info->texture[0]
				[TEXHEIGHT * wall_info->tex_y + wall_info->tex_x];
		if (wall_info->side == 1 && wall_info->ray_diry < 0)
			color = info->texture[2]
				[TEXHEIGHT * wall_info->tex_y + wall_info->tex_x];
		if (wall_info->side == 1 && wall_info->ray_diry > 0)
			color = info->texture[3]
				[TEXHEIGHT * wall_info->tex_y + wall_info->tex_x];
		info->buf[y][x] = color;
	}
}

void	calc_tex(t_wall_info *wall_info)
{
	if (wall_info->side == 0 && wall_info->ray_dirx > 0)
		wall_info->tex_x = TEXWIDTH - wall_info->tex_x - 1;
	if (wall_info->side == 1 && wall_info->ray_diry < 0)
		wall_info->tex_x = TEXWIDTH - wall_info->tex_x - 1;
	wall_info->step = 1.0 * TEXHEIGHT / wall_info->line_height;
}

void	calc_line_height(t_game *info, t_wall_info *wall_info)
{
	wall_info->line_height = (int)(info->h / wall_info->perp_wall_dist);
	wall_info->draw_start = -wall_info->line_height / 2 + info->h / 2;
	if (wall_info->draw_start < 0)
		wall_info->draw_start = 0;
	wall_info->draw_end = wall_info->line_height / 2 + info->h / 2;
	if (wall_info->draw_end >= info->h)
		wall_info->draw_end = info->h - 1;
}
