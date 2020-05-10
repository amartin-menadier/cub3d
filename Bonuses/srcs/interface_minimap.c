/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	double
minimap_data(t_data *data, int mod)
{
	double	ret;
	int		size_in_pxl;
	int		cell_size;
	int		margin;

	ret = 0;
	size_in_pxl = fmin(data->win.size.y / 3, data->win.size.x / 4);
	cell_size = size_in_pxl / MINIMAP_CELLS;
	size_in_pxl = cell_size * MINIMAP_CELLS;
	margin = fmax(cell_size / 8, 1);
	if (mod == SIZE_IN_PXL)
		ret = size_in_pxl;
	if (mod == CELL_SIZE)
		ret = cell_size;
	if (mod == MARGIN || mod == DRAW_START)
		ret = margin;
	if (mod == DRAW_END)
		ret = margin + size_in_pxl;
	if (mod == RADIUS)
		ret = size_in_pxl / 2.0;
	if (mod == CENTER)
		ret = size_in_pxl / 2.0 + margin;
	return (ret);
}

	t_dbl
get_minimap_cell(t_data *data, t_int pxl, t_dbl *cam)
{
	t_dbl	cell;
	double	first_cell;
	int		step;
	t_dbl	*cell_ptr;

	cell_ptr = &cell;
	first_cell = cam->x - (MINIMAP_CELLS) / 2.0;
	step = minimap_data(data, DRAW_END) - pxl.x;
	cell.x = first_cell + step / minimap_data(data, CELL_SIZE);
	first_cell = cam->z - (MINIMAP_CELLS) / 2.0;
	step = (pxl.y - minimap_data(data, DRAW_START));
	cell.z = first_cell + step / minimap_data(data, CELL_SIZE);
	if (fabs(cell.x - cam->x) > 0.5
			|| fabs(cell.z - cam->z) > 0.5
			|| hypot((cell.x - cam->x), (cell.z - cam->z)) > 0.5)
		cell = rotate_point(data->angle.x + PI / 2, cam, cell_ptr);
	return (cell);
}

	int
get_minimap_color(t_data *data, t_int pxl, double perimeter_dist)
{
	int		color;
	char	value;
	t_dbl	cell;

	cell = get_minimap_cell(data, pxl, &data->cam);
	if (cell.x >= data->map_size.x
			|| cell.z >= data->map_size.z
			|| cell.x < 0 || cell.z < 0)
		value = (char)NULL;
	else
		value = data->map[(int)cell.z][(int)cell.x];
	if (value == ' ' || value == (char)NULL)
		color = GREY;
	if (value == '0' || value >= '2' || data->skybox[0][0])
		color = WHITE;
	if ((value == '1' && !data->skybox[0][0]) || perimeter_dist <= 2)
		color = BLACK;
	color = get_avatar_color(data, &data->piclib.avatar, cell, color);
	return (color);
}

	void
draw_minimap_column(t_data *data, t_int pxl, t_int center, double radius)
{
	double	ctr_dist;
	int		color;
	double	perimeter_dist;

	ctr_dist = hypot(pxl.x - center.x, pxl.y - center.y);
	perimeter_dist = radius - ctr_dist;
	if (ctr_dist > radius)
		return ;
	color = get_minimap_color(data, pxl, perimeter_dist);
	if (color != GREY)
		put_pixel(&data->win, pxl, color);
}

	void
draw_minimap(t_data *data, t_int center, double radius)
{
	t_int	pxl;
	int		draw_start;
	int		draw_end;

	draw_start = minimap_data(data, DRAW_START);
	draw_end = minimap_data(data, DRAW_END);
	pxl.x = draw_start;
	while (pxl.x < draw_end)
	{
		pxl.y = draw_start;
		while (pxl.y < draw_end)
		{
			draw_minimap_column(data, pxl, center, radius);
			pxl.y++;
		}
		pxl.x++;
	}
}

