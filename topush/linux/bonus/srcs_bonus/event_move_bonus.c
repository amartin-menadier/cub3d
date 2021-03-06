/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/23 20:34:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void
	move_forward(t_data *data, char **map, t_dbl *cam, t_dbl dir)
{
	int new_x;
	int	new_z;

	new_x = cam->x + dir.x * MOVE_SPEED;
	new_z = cam->z + dir.z * MOVE_SPEED;
	if (map[new_z][new_x] && map[new_z][new_x] >= STAIRS_DOWN)
		load_new_level(data, map[new_z][new_x]);
	if (!is_obstacle(map[(int)cam->z][(int)(cam->x + dir.x * MOVE_SPEED)]))
		cam->x += dir.x * MOVE_SPEED;
	if (!is_obstacle(map[(int)(cam->z + dir.z * MOVE_SPEED)][(int)cam->x]))
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
	if (!is_obstacle(map[(int)cam->z][(int)new_x]))
		cam->x -= dir.x * MOVE_SPEED;
	if (!is_obstacle(map[(int)new_z][(int)cam->x]))
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
	if (!is_obstacle(map[(int)cam->z][(int)new_x]))
		cam->x += dir.z * MOVE_SPEED;
	if (!is_obstacle(map[(int)new_z][(int)cam->x]))
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
	if (!is_obstacle(map[(int)cam->z][(int)new_x]))
		cam->x -= dir.z * MOVE_SPEED;
	if (!is_obstacle(map[(int)new_z][(int)cam->x]))
		cam->z += dir.x * MOVE_SPEED;
}

void
	move(t_data *data, char **map, t_dbl *cam, int key)
{
	t_dbl	dir;

	dir.x = cos(data->angle.x);
	dir.z = sin(data->angle.x);
	if (key == Z || key == W)
		move_forward(data, map, cam, dir);
	if (key == Q || key == A)
		move_left(data, map, cam, dir);
	if (key == S)
		move_backward(data, map, cam, dir);
	if (key == D)
		move_right(data, map, cam, dir);
}
