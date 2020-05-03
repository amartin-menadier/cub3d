/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	t_img
get_wall_img(t_data *data, t_piclib piclib, t_dbl ray)
{
	t_img	wall;
	int		side;

	side = perform_DDA(data, data->set.pos, ray, 1);
	if (side == EA)
		wall = piclib.ea;
	else if (side == SO)
		wall = piclib.so;
	else if (side == WE)
		wall = piclib.we;
	else if (side == NO)
		wall = piclib.no;
	else
		wall.ptr = NULL;
		//verifier la pertinence de ce cas d'erreur suivant
//	if (text_img->size.x != text_img->size.y)
//		close_program(data, "wall texture shall be a square", "");
	return (wall);
}

	int
get_wall_x(t_data *data, t_img wall, t_dbl ray, double perp_wall_dist)
{
	int		wall_pxl_x;
	double	step;

	if (!(((int)perform_DDA(data, data->set.pos, ray, 1)) % 2))
		step = perp_wall_dist * ray.y + data->set.pos.y;
	else
		step = perp_wall_dist * ray.x + data->set.pos.x;
	step -= floor(step);
	wall_pxl_x = step * wall.size.x;
	if (wall_pxl_x < 0 || wall_pxl_x >= wall.size.x)
		wall_pxl_x = -1;
	return (wall_pxl_x);
}

	int
get_wall_y(t_data *data, t_img wall, t_int scr, double perp_wall_dist)
{
	int		wall_pxl_y;
	double	step;
	int		line_height;


	line_height = set_drawing_limit(data->set.win_size, perp_wall_dist, 4);
	step = 1.00 * ((line_height - data->set.win_size.y) / 2 + scr.y);
	step /= line_height;
	wall_pxl_y = step * wall.size.y;
	if (wall_pxl_y < 0 || wall_pxl_y >= wall.size.y)
		wall_pxl_y = -1;
	return (wall_pxl_y);
}

	void
draw_wall_column(t_data *data, t_int scr, t_dbl ray, double perp_wall_dist)
{
	t_img	wall;
	t_int	wall_pxl;
	int		draw_end;
	int		color;

	wall = get_wall_img(data, data->piclib, ray);
	draw_end = set_drawing_limit(data->set.win_size, perp_wall_dist, 2);
	wall_pxl.x = get_wall_x(data, wall, ray, perp_wall_dist);
	while (scr.y < draw_end)
	{
		wall_pxl.y = get_wall_y(data, wall, scr, perp_wall_dist);
		color = get_img_color(wall, wall_pxl.x, wall_pxl.y, wall.size);
		put_pixel(&data->scr, scr, color);
		scr.y++;
	}
}

