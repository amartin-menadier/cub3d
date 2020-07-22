/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_sprites_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:37:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void
	get_sprites_in_map(t_data *data, char **map)
{
	t_int	cam;
	int		i;

	if (data->spr != NULL)
		free(data->spr);
	if (!(data->spr = malloc(sizeof(double *) * 3 * data->spr_count)))
		close_program(data, "Couldn't allocate mem for spr", "");
	cam.z = 1;
	i = 0;
	while (cam.z < data->map_size.z - 1 && i < data->spr_count)
	{
		cam.x = 0;
		while (cam.x < data->map_size.x && i < data->spr_count)
		{
			if (map[cam.z][cam.x] >= '2' && map[cam.z][cam.x] <= '9')
			{
				data->spr[i].x = cam.x + 0.5;
				data->spr[i].y = drand48() * data->win.size.y / 2.0;
				data->spr[i].z = cam.z + 0.5;
				i++;
			}
			cam.x++;
		}
		cam.z++;
	}
}

double
	sprite_data(t_data *data, t_dbl transform, t_int win, int mod)
{
	double	center_x;
	t_int	length;
	int		ret;
	int		vertical_look;

	ret = 0;
	vertical_look = data->cam.y + sin(data->angle.y) * (win.y);
	center_x = ((data->win.size.x / 2) * (1 + transform.x / transform.z));
	length.y = abs((int)(win.y / (transform.z)));
	length.x = abs((int)(win.x / (2 * transform.z)));
	if (mod == CENTER_X)
		return (center_x);
	if (mod == WIDTH)
		return (length.x);
	if (mod == HEIGHT)
		return (length.y);
	if (mod == DRAW_START_X)
		return ((ret = center_x - length.x / 2) < 0 ? 0 : ret);
	if (mod == DRAW_END_X)
		return ((ret = length.x / 2 + center_x) >= win.x ? win.x : ret);
	if (mod == DRAW_START_Y)
		return ((ret = vertical_look - length.y / 2) < 0 ? 0 : ret);
	if (mod == DRAW_END_Y)
		return ((ret = vertical_look + length.y / 2) >= win.y ? win.y : ret);
	return (-9999);
}

void
	sort_sprites(t_dbl cam, t_dbl *spr, int spr_count)
{
	int		i;
	int		j;
	int		k;
	t_dbl	tmp_spr;

	i = 0;
	while (i < spr_count - 1)
	{
		k = 0;
		j = i;
		while (++j < spr_count)
		{
			if ((dist(cam, spr[i]) < dist(cam, spr[j]) && i < j)
				|| (dist(cam, spr[i]) > dist(cam, spr[j]) && i > j))
			{
				k++;
				tmp_spr = spr[i];
				spr[i] = spr[j];
				spr[j] = tmp_spr;
			}
		}
		i = (k == 0) ? i + 1 : i;
	}
}

int
	sprite_player_same_cell(t_data *data, int i)
{
	t_int	spr;
	t_int	player;

	spr.x = (int)data->spr[i].x;
	spr.y = (int)data->spr[i].z;
	player.x = (int)data->cam.x;
	player.y = (int)data->cam.z;
	if (spr.x == player.x && spr.z == player.z)
		return (1);
	else
		return (0);
}
