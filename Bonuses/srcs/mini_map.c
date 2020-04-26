/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int first_pxl(t_minimap *map, t_int pxl){if (pxl.x == map->draw_start.x && pxl.y == map->draw_start.y)return (1);else return (0);}

	void
set_minimap_limits(double pos, double *case_min, double *case_max)
{
	*case_min = pos - (MINIMAP_SIZE) / 2;
	*case_max = pos + (MINIMAP_SIZE) / 2;
}

	void
get_minimap_avatar(t_data *data, t_img *avatar)
{
	char *path;

	if (data->life.value >= 80)
		path = ft_strdup("./textures/intellolcut.xpm");
	else if (data->life.value >= 33)
		path = ft_strdup("./textures/grinmacing.xpm");
	else
		path = ft_strdup("./textures/crying.xpm");
	ft_putstr_fd("\nMINIMAP19", 1);
	create_img(data, path, avatar);
	free(path);
	path = NULL;
}

	void
draw_minimap(t_data *data, t_settings *settings, t_minimap *map)
{
	t_int	pxl;

		ft_putstr_fd("\nMINIMAP01", 1);
	set_minimap_limits(data->frame.pos.x, &map->case_min.x, &map->case_max.x);
	set_minimap_limits(data->frame.pos.y, &map->case_min.y, &map->case_max.y);
	get_minimap_avatar(data, &data->piclib.avatar);
	pxl.x = map->draw_start.x;
		ft_putstr_fd("\nMINIMAP05", 1);
	while (pxl.x < map->draw_end.x)
	{
	if (pxl.x == map->draw_start.x){ft_putstr_fd("\nMINIMAP06", 1);}
		pxl.y = map->draw_start.y;
		while (pxl.y < map->draw_end.y)
		{
	if (first_pxl(map, pxl))ft_putstr_fd("\nMINIMAP07", 1);
			draw_minimap_column(data, settings, map, pxl);
			pxl.y++;
		}
		pxl.x++;
	}
	data->map.done = 1;
}

	t_dbl
rotate_minimap(t_data *data, t_dbl pos)
{
	double	rot;
	double	old_x;
	t_dbl	ctr;
/*	double	dir_y;

	dir_y = data->frame.dir.y;
	/// (sqrt(2) / 2);
	if (fabs(dir_y) > 1 && dir_y < 0)
		dir_y = -1;
	else if (fabs(dir_y) > 1 && dir_y > 0)
		dir_y = 1;
	if (!(rot = acos(-dir_y)))
		rot = 0;
	if (data->frame.dir.x > 0)
		rot = PI + acos(dir_y);
	rot = -rot;
	*/
	rot = -data->frame.plane.angle;
	ctr.x = (double)data->frame.pos.x;
	ctr.y = (double)data->frame.pos.y;
	old_x = pos.x;
	pos.x = (pos.x - ctr.x) * cos(rot) - (pos.y - ctr.y) * sin(rot) + ctr.x;
	pos.y = - (old_x - ctr.x) * sin(rot) - (pos.y - ctr.y) * cos(rot) + ctr.y;
	return (pos);
}

	int
draw_minimap_avatar(t_data *data, t_frame *frame, t_dbl pos, int color)
{
	t_int		avat_pxl;
	t_minimap	*map;
	t_img		*avatar;

	map = &data->map;
	avatar = &data->piclib.avatar;
	if (fabs(pos.x - frame->pos.x) > 0.5 || fabs(pos.y - frame->pos.y) > 0.5)
		return (color);
	if ((hypot((pos.x - frame->pos.x), (pos.y - frame->pos.y))) > 0.5)
		return (color);
//	get_minimap_face(data, &data->map);
	avat_pxl.x = (int)((frame->pos.x - pos.x + 0.5) * avatar->size.x);
	avat_pxl.y = (int)((pos.y - frame->pos.y + 0.5) * avatar->size.y);
	if (avatar->colors[(avatar->size.x * avat_pxl.y + avat_pxl.x)])
		color = avatar->colors[(avatar->size.x * avat_pxl.y + avat_pxl.x)];
	return (color);
}

	void
draw_minimap_column(t_data *data, t_settings *settings, t_minimap *map, t_int pxl)
{
	double	ctr_dist;
	char	value;
	t_dbl	pxl_pos;
	int		color;
	
	ctr_dist = hypot(pxl.x - 1.0 * map->center.x, pxl.y - 1.0 * map->center.y);
	if (ctr_dist > map->radius)
		return ;
	pxl_pos.x = map->case_min.x + (pxl.x - map->draw_start.x) * map->step_in_case;
	pxl_pos.y = map->case_min.y + (pxl.y - map->draw_start.y) * map->step_in_case;
	if (fabs(pxl_pos.x - data->frame.pos.x) > 0.5
			|| fabs(pxl_pos.y - data->frame.pos.y) > 0.5
			|| hypot((pxl_pos.x - data->frame.pos.x), (pxl_pos.y - data->frame.pos.y)) > 0.5)
	pxl_pos = rotate_minimap(data, pxl_pos);
	if (pxl_pos.x >= settings->map_size.x || pxl_pos.y >= settings->map_size.y
			|| pxl_pos.x < 0 || pxl_pos.y < 0)
		value = (char)NULL;
	else
		value = settings->map[(int)pxl_pos.y][(int)pxl_pos.x];
	if (value == ' ' || value == (char)NULL)
		color = GREY;
	if (value == '0' || value >= '2' || data->skybox)
		color = WHITE;
	if ((value == '1' && !data->skybox) || map->radius - ctr_dist <= 2)
		color = BLACK;
	color = draw_minimap_avatar(data, &data->frame, pxl_pos, color);
	if (color != GREY)
		put_pixel(&data->scr, pxl, color);
}
