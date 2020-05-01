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
move_forward(t_set *set, char **map, t_dbl dir)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x + dir.x * MOVE_SPEED)] != 49)
		set->pos.x += dir.x * MOVE_SPEED;
	if(map[(int)(pos.y + dir.y * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y += dir.y * MOVE_SPEED;
}

	void
move_backward(t_set *set, char **map, t_dbl dir)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x - dir.x * MOVE_SPEED)] != 49)
		set->pos.x -= dir.x * MOVE_SPEED;
	if(map[(int)(pos.y - dir.y * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y -= dir.y * MOVE_SPEED;
}

	void
move_right(t_set *set, char **map, t_dbl dir)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x + dir.y * MOVE_SPEED)] != 49)
		set->pos.x += dir.y * MOVE_SPEED;
	if(map[(int)(pos.y - dir.x * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y -= dir.x * MOVE_SPEED;
}

	void
move_left(t_set *set, char **map, t_dbl dir)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x - dir.y * MOVE_SPEED)] != 49)
		set->pos.x -= dir.y * MOVE_SPEED;
	if(map[(int)(pos.y + dir.x * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y += dir.x * MOVE_SPEED;
}

	void
move(t_set *set, char **map, int key)
{
	t_dbl	dir;

	dir.x = cos(set->angle);
	dir.y = sin(set->angle);
	if (key == Z)
		move_forward(set, map, dir);
	if (key == Q)
		move_left(set, map, dir);
	if (key == S)
		move_backward(set, map, dir);
	if (key == D)
		move_right(set, map, dir);
}
