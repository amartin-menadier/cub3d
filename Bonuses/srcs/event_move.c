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
move_forward(char **map, t_dbl *cam, t_dbl dir)
{
	if(map[(int)cam->z][(int)(cam->x + dir.x * MOVE_SPEED)] != WALL)
		cam->x += dir.x * MOVE_SPEED;
	if(map[(int)(cam->z + dir.z * MOVE_SPEED)][(int)cam->x] != WALL)
		cam->z += dir.z * MOVE_SPEED;
}

	void
move_backward(char **map, t_dbl *cam, t_dbl dir)
{
	if(map[(int)cam->z][(int)(cam->x - dir.x * MOVE_SPEED)] != WALL)
		cam->x -= dir.x * MOVE_SPEED;
	if(map[(int)(cam->z - dir.z * MOVE_SPEED)][(int)cam->x] != WALL)
		cam->z -= dir.z * MOVE_SPEED;
}

	void
move_right(char **map, t_dbl *cam, t_dbl dir)
{
	if(map[(int)cam->z][(int)(cam->x + dir.z * MOVE_SPEED)] != WALL)
		cam->x += dir.z * MOVE_SPEED;
	if(map[(int)(cam->z - dir.x * MOVE_SPEED)][(int)cam->x] != WALL)
		cam->z -= dir.x * MOVE_SPEED;
}

	void
move_left(char **map, t_dbl *cam, t_dbl dir)
{
	if(map[(int)cam->z][(int)(cam->x - dir.z * MOVE_SPEED)] != WALL)
		cam->x -= dir.z * MOVE_SPEED;
	if(map[(int)(cam->z + dir.x * MOVE_SPEED)][(int)cam->x] != WALL)
		cam->z += dir.x * MOVE_SPEED;
}

	void
move(t_data *data, char **map, t_dbl *cam, int key)
{
	t_dbl	dir;

	data->time = clock();
	if (key == SPACE && data->current_event != KNEEL)
		data->current_event = JUMP;
	if (key == V && data->current_event != JUMP)// a modifier
		data->current_event = KNEEL;
	dir.x = cos(data->angle.x);
	dir.z = sin(data->angle.x);
	if (key == Z)
		move_forward(map, cam, dir);
	if (key == Q)
		move_left(map, cam, dir);
	if (key == S)
		move_backward(map, cam, dir);
	if (key == D)
		move_right(map, cam, dir);
}
