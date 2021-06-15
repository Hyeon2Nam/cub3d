/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:03:04 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/01 14:39:18 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_image(t_game *info, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
		&img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->size_l, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			texture[img->width * y + x] = img->data[img->width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_game *info)
{
	t_img img;

	load_image(info, info->texture[0], info->img.no, &img);
	load_image(info, info->texture[1], info->img.so, &img);
	load_image(info, info->texture[2], info->img.we, &img);
	load_image(info, info->texture[3], info->img.ea, &img);
}

void	draw(t_game *info)
{
	int x;
	int y;

	y = -1;
	while (++y < info->h)
	{
		x = -1;
		while (++x < info->w)
			info->img.data[y * info->w + x] = info->buf[y][x];
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
