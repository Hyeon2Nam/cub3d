/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:52:53 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/14 12:33:44 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	info_init(t_game *info)
{
	info->mlx = mlx_init();
	info->key.key_a = 0;
	info->key.key_w = 0;
	info->key.key_s = 0;
	info->key.key_d = 0;
	info->key.key_ar_l = 0;
	info->key.key_ar_r = 0;
	info->key.key_esc = 0;
	info->move_speed = 0.05;
	info->rot_speed = 0.05;
}

int		set_buf_and_tex(t_game *info)
{
	int i;

	if (!(info->buf = (int **)malloc(sizeof(int *) * info->h)))
		return (-1);
	i = -1;
	while (++i < info->h)
		if (!(info->buf[i] = (int *)ft_calloc(sizeof(int), info->w)))
			return (-1);
	i = -1;
	while (++i < 4)
		if (!(info->texture[i] =
			(int *)ft_calloc(sizeof(int), TEXHEIGHT * TEXWIDTH)))
			return (-1);
	return (0);
}

int		is_current_file(char *str, char *file)
{
	int slen;
	int clen;

	slen = ft_strlen(str);
	clen = ft_strlen(file);
	if (slen < 4)
		error_handler("Error\nInput .cub file");
	while (clen)
	{
		if (str[slen--] != file[clen--])
			error_handler("Error\nInput .cub file");
	}
	return (1);
}

int		data_checking(t_game *map, char data, int i, int j)
{
	int overlap;

	overlap = 0;
	if (ft_strchr("10NSWE ", data))
	{
		if (!ft_isdigit(data))
		{
			map->map_info.map[i][j] = 0;
			if (ft_strchr("NSWE", data))
			{
				overlap++;
				set_dir(map, data, i, j);
			}
		}
		else
			map->map_info.map[i][j] = data - '0';
	}
	else
		error_handler("Error\ninvaild map (Unknow sign)");
	return (overlap);
}
