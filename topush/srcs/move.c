/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
move_forward(t_frame *frame, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x + frame->dir.x * move_speed)] == '0')
		frame->pos.x += frame->dir.x * move_speed;
	if(map[(int)(pos.y + frame->dir.y * move_speed)][(int)pos.x] == '0')
		frame->pos.y += frame->dir.y * move_speed;
}

	void
move_backward(t_frame *frame, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x - frame->dir.x * move_speed)] == '0')
		frame->pos.x -= frame->dir.x * move_speed;
	if(map[(int)(pos.y - frame->dir.y * move_speed)][(int)pos.x] == '0')
		frame->pos.y -= frame->dir.y * move_speed;
}

	void
move_right(t_frame *frame, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x - frame->dir.y * move_speed)] == '0')
		frame->pos.x -= frame->dir.y * move_speed;
	if(map[(int)(pos.y + frame->dir.x * move_speed)][(int)pos.x] == '0')
		frame->pos.y += frame->dir.x * move_speed;
}

	void
move_left(t_frame *frame, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x + frame->dir.y * move_speed)] == '0')
		frame->pos.x += frame->dir.y * move_speed;
	if(map[(int)(pos.y - frame->dir.x * move_speed)][(int)pos.x] == '0')
		frame->pos.y -= frame->dir.x * move_speed;
}
