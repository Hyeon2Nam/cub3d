/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:19:09 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/12 16:14:29 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_dir(t_game *map, char dir, int i, int j)
{
	map->posx = i + 0.5;
	map->posy = j + 0.5;
	map->dir = dir;
	if (dir == 'N')
	{
		map->dirx = -1.0;
		map->diry = 0.0;
		map->planex = 0.0;
		map->planey = 0.66;
	}
	if (dir == 'S')
	{
		map->dirx = 1.0;
		map->diry = 0.0;
		map->planex = 0.0;
		map->planey = -0.66;
	}
	else
		set_dir_ew(map, dir);
}

void	set_dir_ew(t_game *map, char dir)
{
	if (dir == 'E')
	{
		map->dirx = 0.0;
		map->diry = 1.0;
		map->planex = 0.66;
		map->planey = 0.0;
	}
	if (dir == 'W')
	{
		map->dirx = 0.0;
		map->diry = -1.0;
		map->planex = -0.66;
		map->planey = 0.0;
	}
}
