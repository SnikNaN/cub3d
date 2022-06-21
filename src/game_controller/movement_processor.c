/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:42:57 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/20 19:08:13 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	turn_right(t_dataset *set)
{
	double	*dir[2];
	double	*plane[2];
	double	old_dir_x;
	double	old_plane_x;

	dir[X] = &set->game->hero_pos.dir_x;
	dir[Y] = &set->game->hero_pos.dir_y;
	plane[X] = &set->game->hero_pos.cam_plane_x;
	plane[Y] = &set->game->hero_pos.cam_plane_y;
	old_dir_x = *(dir[X]);
	*(dir[X]) = *(dir[X]) * cos(RT_SPEED) - *(dir[Y]) * sin(RT_SPEED);
	*(dir[Y]) = old_dir_x * sin(RT_SPEED) + *(dir[Y]) * cos(RT_SPEED);
	old_plane_x = *(plane[X]);
	*(plane[X]) = *(plane[X]) * cos(RT_SPEED) - *(plane[Y]) * sin(RT_SPEED);
	*(plane[Y]) = old_plane_x * sin(RT_SPEED) + *(plane[Y]) * cos(RT_SPEED);
}

static void	turn_left(t_dataset *set)
{
	double	*dir[2];
	double	*plane[2];
	double	old_dir_x;
	double	old_plane_x;

	dir[X] = &set->game->hero_pos.dir_x;
	dir[Y] = &set->game->hero_pos.dir_y;
	plane[X] = &set->game->hero_pos.cam_plane_x;
	plane[Y] = &set->game->hero_pos.cam_plane_y;
	old_dir_x = *(dir[X]);
	*(dir[X]) = *(dir[X]) * cos(-RT_SPEED) - *(dir[Y]) * sin(-RT_SPEED);
	*(dir[Y]) = old_dir_x * sin(-RT_SPEED) + *(dir[Y]) * cos(-RT_SPEED);
	old_plane_x = *(plane[X]);
	*(plane[X]) = *(plane[X]) * cos(-RT_SPEED) - *(plane[Y]) * sin(-RT_SPEED);
	*(plane[Y]) = old_plane_x * sin(-RT_SPEED) + *(plane[Y]) * cos(-RT_SPEED);
}

static int	check_mouse(t_dataset *set)
{
	int	x;
	int	move;

	mlx_mouse_get_pos(set->rend->win, &x, &move);
	move = 0;
	if (x < (W_RES / 2 - 1))
	{
		move = 1;
		set->game->hero_pos.turn_left = 1;
	}
	else if (x > (W_RES / 2 + 1))
	{
		move = 1;
		set->game->hero_pos.turn_right = 1;
	}
	mlx_mouse_move(set->rend->win, W_RES / 2, 0);
	return (move);
}

void	movement_processor(t_dataset *set)
{
	int	mouse;

	mouse = check_mouse(set);
	if (set->game->hero_pos.move_front)
		move_forward(set);
	if (set->game->hero_pos.move_back)
		move_back(set);
	if (set->game->hero_pos.move_left)
		move_left(set);
	if (set->game->hero_pos.move_right)
		move_right(set);
	if (set->game->hero_pos.turn_left)
		turn_left(set);
	if (set->game->hero_pos.turn_right)
		turn_right(set);
	if (mouse)
	{
		set->game->hero_pos.turn_left = 0;
		set->game->hero_pos.turn_right = 0;
	}
}
