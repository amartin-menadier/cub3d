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
move_forward(t_set *set, char **map)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x + set->dir.x * MOVE_SPEED)] != 49)
		set->pos.x += set->dir.x * MOVE_SPEED;
	if(map[(int)(pos.y + set->dir.y * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y += set->dir.y * MOVE_SPEED;
}

	void
move_backward(t_set *set, char **map)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x - set->dir.x * MOVE_SPEED)] != 49)
		set->pos.x -= set->dir.x * MOVE_SPEED;
	if(map[(int)(pos.y - set->dir.y * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y -= set->dir.y * MOVE_SPEED;
}

	void
move_right(t_set *set, char **map)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x + set->dir.y * MOVE_SPEED)] != 49)
		set->pos.x += set->dir.y * MOVE_SPEED;
	if(map[(int)(pos.y - set->dir.x * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y -= set->dir.x * MOVE_SPEED;
}

	void
move_left(t_set *set, char **map)
{
	t_dbl	pos;

	pos.x = set->pos.x;
	pos.y = set->pos.y;
	if(map[(int)pos.y][(int)(pos.x - set->dir.y * MOVE_SPEED)] != 49)
		set->pos.x -= set->dir.y * MOVE_SPEED;
	if(map[(int)(pos.y + set->dir.x * MOVE_SPEED)][(int)pos.x] != 49)
		set->pos.y += set->dir.x * MOVE_SPEED;
}
