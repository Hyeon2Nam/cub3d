/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:17:40 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/20 15:33:59 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		key_press(int key, t_game *info)
{
	if (key == K_ESC)
	{
		mlx_destroy_window(info->mlx, info->win);
		exit(0);
	}
	else if (key == K_W || key == K_AR_U)
		info->key.key_w = 1;
	else if (key == K_A)
		info->key.key_a = 1;
	else if (key == K_S || key == K_AR_D)
		info->key.key_s = 1;
	else if (key == K_D)
		info->key.key_d = 1;
	else if (key == K_AR_L)
		info->key.key_ar_l = 1;
	else if (key == K_AR_R)
		info->key.key_ar_r = 1;
	return (0);
}

int		key_release(int key, t_game *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W || key == K_AR_U)
		info->key.key_w = 0;
	else if (key == K_A)
		info->key.key_a = 0;
	else if (key == K_S || key == K_AR_D)
		info->key.key_s = 0;
	else if (key == K_D)
		info->key.key_d = 0;
	else if (key == K_AR_L)
		info->key.key_ar_l = 0;
	else if (key == K_AR_R)
		info->key.key_ar_r = 0;
	return (0);
}

int		key_exit(t_game *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}
