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
	t_coord	pos;

	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x + frame->dir.x * MOVE_SPEED)] != 49)
		frame->pos.x += frame->dir.x * MOVE_SPEED;
	if(map[(int)(pos.y + frame->dir.y * MOVE_SPEED)][(int)pos.x] != 49)
		frame->pos.y += frame->dir.y * MOVE_SPEED;
}

	void
move_backward(t_frame *frame, char **map)
{
	t_coord	pos;

	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x - frame->dir.x * MOVE_SPEED)] != 49)
		frame->pos.x -= frame->dir.x * MOVE_SPEED;
	if(map[(int)(pos.y - frame->dir.y * MOVE_SPEED)][(int)pos.x] != 49)
		frame->pos.y -= frame->dir.y * MOVE_SPEED;
}

	void
move_right(t_frame *frame, char **map)
{
	t_coord	pos;

	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x - frame->dir.y * MOVE_SPEED)] != 49)
		frame->pos.x -= frame->dir.y * MOVE_SPEED;
	if(map[(int)(pos.y + frame->dir.x * MOVE_SPEED)][(int)pos.x] != 49)
		frame->pos.y += frame->dir.x * MOVE_SPEED;
}

	void
move_left(t_frame *frame, char **map)
{
	t_coord	pos;

	pos.x = frame->pos.x;
	pos.y = frame->pos.y;
	if(map[(int)pos.y][(int)(pos.x + frame->dir.y * MOVE_SPEED)] != 49)
		frame->pos.x += frame->dir.y * MOVE_SPEED;
	if(map[(int)(pos.y - frame->dir.x * MOVE_SPEED)][(int)pos.x] != 49)
		frame->pos.y -= frame->dir.x * MOVE_SPEED;
}
