/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:01:32 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/12 16:13:46 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	key_update(t_game *info)
{
	double old_dirx;
	double old_planex;

	old_dirx = info->dirx;
	old_planex = info->planex;
	if (info->key.key_w || info->key.key_s)
		move_up_down(&info);
	if (info->key.key_a || info->key.key_d)
		move_left_right(&info);
	if (info->key.key_ar_l || info->key.key_ar_r)
		move_camera(&info, old_dirx, old_planex);
	if (info->key.key_esc)
		exit(0);
}

void	move_up_down(t_game **info)
{
	if ((*info)->key.key_w)
	{
		if (!(*info)->map_info.map[(int)((*info)->posx + (*info)->dirx *
			(*info)->move_speed)][(int)((*info)->posy)])
			(*info)->posx += (*info)->dirx * (*info)->move_speed;
		if (!(*info)->map_info.map[(int)((*info)->posx)][(int)((*info)->posy +
			(*info)->diry * (*info)->move_speed)])
			(*info)->posy += (*info)->diry * (*info)->move_speed;
	}
	if ((*info)->key.key_s)
	{
		if (!(*info)->map_info.map[(int)((*info)->posx - (*info)->dirx *
			(*info)->move_speed)][(int)((*info)->posy)])
			(*info)->posx -= (*info)->dirx * (*info)->move_speed;
		if (!(*info)->map_info.map[(int)((*info)->posx)][(int)((*info)->posy -
			(*info)->diry * (*info)->move_speed)])
			(*info)->posy -= (*info)->diry * (*info)->move_speed;
	}
}

void	move_left_right(t_game **info)
{
	if ((*info)->key.key_a)
	{
		if (!(*info)->map_info.map[(int)((*info)->posx - (*info)->diry *
			(*info)->move_speed)][(int)((*info)->posy)])
			(*info)->posx -= (*info)->diry * (*info)->move_speed;
		if (!(*info)->map_info.map[(int)((*info)->posx)][(int)((*info)->posy +
			(*info)->dirx * (*info)->move_speed)])
			(*info)->posy += (*info)->dirx * (*info)->move_speed;
	}
	if ((*info)->key.key_d)
	{
		if (!(*info)->map_info.map[(int)((*info)->posx + (*info)->diry *
			(*info)->move_speed)][(int)((*info)->posy)])
			(*info)->posx += (*info)->diry * (*info)->move_speed;
		if (!(*info)->map_info.map[(int)((*info)->posx)][(int)((*info)->posy -
			(*info)->dirx * (*info)->move_speed)])
			(*info)->posy -= (*info)->dirx * (*info)->move_speed;
	}
}

void	move_camera(t_game **info, double old_dirx, double old_planex)
{
	if ((*info)->key.key_ar_r)
	{
		(*info)->dirx = (*info)->dirx * cos(-(*info)->rot_speed) -
			(*info)->diry * sin(-(*info)->rot_speed);
		(*info)->diry = old_dirx * sin(-(*info)->rot_speed) +
			(*info)->diry * cos(-(*info)->rot_speed);
		(*info)->planex = (*info)->planex * cos(-(*info)->rot_speed) -
			(*info)->planey * sin(-(*info)->rot_speed);
		(*info)->planey = old_planex * sin(-(*info)->rot_speed) +
			(*info)->planey * cos(-(*info)->rot_speed);
	}
	if ((*info)->key.key_ar_l)
	{
		(*info)->dirx = (*info)->dirx * cos((*info)->rot_speed) -
			(*info)->diry * sin((*info)->rot_speed);
		(*info)->diry = old_dirx * sin((*info)->rot_speed) +
			(*info)->diry * cos((*info)->rot_speed);
		(*info)->planex = (*info)->planex * cos((*info)->rot_speed) -
			(*info)->planey * sin((*info)->rot_speed);
		(*info)->planey = old_planex * sin((*info)->rot_speed) +
			(*info)->planey * cos((*info)->rot_speed);
	}
}
