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
get_minimap_face(t_data *data, t_minimap *map)
{
	char *path;

	if (data->life.value >= 80)
		path = ft_strdup("./textures/intellolcut.xpm");
	else if (data->life.value >= 33)
		path = ft_strdup("./textures/grinmacing.xpm");
	else
		path = ft_strdup("./textures/crying.xpm");
	create_img(data, path, &map->face);
	free(path);
	path = NULL;
}

	void
draw_minimap(t_data *data, t_settings *settings, t_minimap *map)
{
	t_int	pxl;

		ft_putstr_fd("\nMINIMAP01", 1);
	set_minimap_limits(data->frame.pos.x, &map->case_min.x, &map->case_max.x);
		ft_putstr_fd("\nMINIMAP02", 1);
	set_minimap_limits(data->frame.pos.y, &map->case_min.y, &map->case_max.y);
		ft_putstr_fd("\nMINIMAP03", 1);
	get_minimap_face(data, map);
		ft_putstr_fd("\nMINIMAP04", 1);
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

	t_coord
rotate_minimap(t_data *data, t_coord pos)
{
	double	rot;
	double	old_x;
	t_coord	ctr;

	if (!(rot = acos(-data->frame.dir.y)))
		rot = 0;
	if (data->frame.dir.x > 0)
		rot = PI + acos(data->frame.dir.y);
	rot = -rot;
	ctr.x = (double)data->frame.pos.x;
	ctr.y = (double)data->frame.pos.y;
	old_x = pos.x;
	pos.x = (pos.x - ctr.x) * cos(rot) - (pos.y - ctr.y) * sin(rot) + ctr.x;
	pos.y = (old_x - ctr.x) * sin(rot) + (pos.y - ctr.y) * cos(rot) + ctr.y;
	return (pos);
}

	int
draw_minimap_face(t_data *data, t_frame *frame, t_coord pos, int color)
{
	t_int		face_pxl;
	t_minimap	*map;

	map = &data->map;
	if (fabs(pos.x - frame->pos.x) > 0.5 || fabs(pos.y - frame->pos.y) > 0.5)
		return (color);
	if ((hypot((pos.x - frame->pos.x), (pos.y - frame->pos.y))) > 0.5)
		return (color);
//	get_minimap_face(data, &data->map);
	face_pxl.x = (int)((frame->pos.x - pos.x + 0.5) * data->map.face.size.x);
	face_pxl.y = (int)((pos.y - frame->pos.y + 0.5) * data->map.face.size.y);
	if (map->face.colors[(map->face.size.x * face_pxl.y + face_pxl.x)])
		color = map->face.colors[(map->face.size.x * face_pxl.y + face_pxl.x)];
	return (color);
}


	void
draw_minimap_column(t_data *data, t_settings *settings, t_minimap *map, t_int pxl)
{
	double	ctr_dist;
	char	value;
	t_coord	pxl_pos;
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
	if (value == '0' || value >= '2')
		color = WHITE;
	if (value == '1' || map->radius - ctr_dist <= 2)
		color = BLACK;
	color = draw_minimap_face(data, &data->frame, pxl_pos, color);
	if (color != GREY)
		put_pixel(&data->img, pxl, color);
}

/*

   value = settings->map
   if ()



   double center_dist = hypot((text.x - radius), (text.y - radius));

   t_coord	case_pos;
   case_pos.x = map->case_min.x;
   t_int	count;
   int		color;


   while (case_pos.x <= map->case_max.x)
   {
   case_pos.y = map->case_min.y;
   while (case_pos.y <= map->case_max.y)
   {
   count.x = 0;
   while (count.x < map->case_size)
   {
   pxl.x = map->draw_start.x + (case_pos.x - map->case_min.x) * map->case_size + count.x;
   count.y = 0;
   while (count.y < map->case_size)
   {
   pxl.y = map->draw_start.y + (case_pos.y - map->case_min.y) * map->case_size + count.y;
//			else if (case_pos.y == (int)data->frame.pos.y && case_pos.x == (int)data->frame.pos.x)
t_int oldpxl;
oldpxl.x = pxl.x;
oldpxl.y = pxl.y;
t_coord case_dbl;
case_dbl.x = 1.0 * case_pos.x + (double)((count.x + 1) / (map->case_size + 1));
case_dbl.y = 1.0 * case_pos.y + (double)((count.y + 1) / (map->case_size + 1));
t_coord pos;
pos.x = data->frame.pos.x;
pos.y = data->frame.pos.y;
if (settings->map[(int)case_pos.y][(int)case_pos.x] == '1')
color = BLACK;
else if (case_dbl.x >= (pos.x) && case_dbl.x <= (pos.x)						&& case_dbl.y >= (pos.y) && case_dbl.y <= (pos.y))
{
color = WHITE;
put_pixel(&data->img, pxl, color);
pxl.x -= (int)((case_dbl.x - pos.x) * (double)map->case_size);
pxl.y -= (int)((case_dbl.y - pos.y) * (double)map->case_size);
double step = 1.0 * map->face.size.y / (map->case_size);
t_coord text;
text.x = (double)(count.x) *step;
text.y = (double)(count.y) *step;
double radius = (double)map->face.size.x / 2;
double rotation = acos(-data->frame.dir.y);
if (data->frame.dir.x > 0)
rotation = PI + acos(data->frame.dir.y);
double oldx = text.x;
text.x = (text.x - radius) * cos(rotation) - (text.y - radius) * sin(rotation) + radius;
text.y = (oldx - radius) * sin(rotation) + (text.y - radius) * cos(rotation) + radius;
double center_dist = hypot((text.x - radius), (text.y - radius));
if (center_dist > radius)
color = WHITE;
else
color = map->face.colors[(map->face.size.x * (int)text.y + (int)text.x)];
}
else 
color = WHITE;
if (settings->map[(int)case_pos.y][(int)case_pos.x] != ' ')
put_pixel(&data->img, pxl, color);
pxl.x = oldpxl.x;
pxl.y = oldpxl.y;
count.y++;
}
count.x++;
}
case_pos.y++;
}
case_pos.x++;
}

data->map.done = 1;
}
*/
