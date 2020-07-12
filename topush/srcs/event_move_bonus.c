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

#include "cub3d_bonus.h"

void
	move_forward(t_data *data, char **map, t_dbl *cam, t_dbl dir)
{
	int new_x;
	int	new_z;

	new_x = cam->x + dir.x * MOVE_SPEED;
	new_z = cam->z + dir.z * MOVE_SPEED;
	if (map[new_z][new_x] && map[new_z][new_x] >= STAIRS_DOWN)
		load_new_level(data, map[new_z][new_x]);
	if (!OBSTACLE(map[(int)cam->z][(int)(cam->x + dir.x * MOVE_SPEED)]))
		cam->x += dir.x * MOVE_SPEED;
	if (!OBSTACLE(map[(int)(cam->z + dir.z * MOVE_SPEED)][(int)cam->x]))
		cam->z += dir.z * MOVE_SPEED;
}

void
	move_backward(t_data *data, char **map, t_dbl *cam, t_dbl dir)
{
	int new_x;
	int	new_z;

	new_x = cam->x - dir.x * MOVE_SPEED;
	new_z = cam->z - dir.z * MOVE_SPEED;
	if (map[new_z][new_x] && map[new_z][new_x] >= STAIRS_DOWN)
		load_new_level(data, map[new_z][new_x]);
	if (!OBSTACLE(map[(int)cam->z][(int)new_x]))
		cam->x -= dir.x * MOVE_SPEED;
	if (!OBSTACLE(map[(int)new_z][(int)cam->x]))
		cam->z -= dir.z * MOVE_SPEED;
}

void
	move_right(t_data *data, char **map, t_dbl *cam, t_dbl dir)
{
	int new_x;
	int	new_z;

	new_x = cam->x + dir.z * MOVE_SPEED;
	new_z = cam->z - dir.x * MOVE_SPEED;
	if (map[new_z][new_x] && map[new_z][new_x] >= STAIRS_DOWN)
		load_new_level(data, map[new_z][new_x]);
	if (!OBSTACLE(map[(int)cam->z][(int)new_x]))
		cam->x += dir.z * MOVE_SPEED;
	if (!OBSTACLE(map[(int)new_z][(int)cam->x]))
		cam->z -= dir.x * MOVE_SPEED;
}

void
	move_left(t_data *data, char **map, t_dbl *cam, t_dbl dir)
{
	int new_x;
	int	new_z;

	new_x = cam->x - dir.z * MOVE_SPEED;
	new_z = cam->z + dir.x * MOVE_SPEED;
	if (map[new_z][new_x] && map[new_z][new_x] >= STAIRS_DOWN)
		load_new_level(data, map[new_z][new_x]);
	if (!OBSTACLE(map[(int)cam->z][(int)new_x]))
		cam->x -= dir.z * MOVE_SPEED;
	if (!OBSTACLE(map[(int)new_z][(int)cam->x]))
		cam->z += dir.x * MOVE_SPEED;
}

void
	move(t_data *data, char **map, t_dbl *cam, int key)
{
	t_dbl	dir;

	if (key == SPACE && data->current_event != KNEEL)
	{
		data->time = clock();
		data->current_event = JUMP;
	}
	if (key == V && data->current_event != JUMP)
		data->current_event = KNEEL;
	dir.x = cos(data->angle.x);
	dir.z = sin(data->angle.x);
	if (key == Z)
		move_forward(data, map, cam, dir);
	if (key == Q)
		move_left(data, map, cam, dir);
	if (key == S)
		move_backward(data, map, cam, dir);
	if (key == D)
		move_right(data, map, cam, dir);
}
