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
*get_wall_img(t_data *data, t_piclib *piclib, t_dbl ray)
{
	t_img	*wall;
	int		side;

	wall = NULL;
	side = perform_DDA(data, data->cam, ray, 1);
	if (side == EA)
		wall = &piclib->ea;
	else if (side == SO)
		wall = &piclib->so;
	else if (side == WE)
		wall = &piclib->we;
	else if (side == NO)
		wall = &piclib->no;
	else
		wall->ptr = NULL;
		//verifier la pertinence de ce cas d'erreur suivant
//	if (text_img->size.x != text_img->size.y)
//		close_program(data, "wall texture shall be a square", "");
	return (wall);
}

	double
img_step(t_data *data, double wall_dist, t_dbl ray, int *pxl_y)
{
	t_dbl	step;
	double	line_height;
	t_int	*win_size;
	int		vertical_look;

	if (pxl_y == NULL)
	{
		if (!(((int)perform_DDA(data, data->cam, ray, 1)) % 2))
			step.x = wall_dist * ray.z + data->cam.z;
		else
			step.x = wall_dist * ray.x + data->cam.x;
		step.x -= floor(step.x);
		return (step.x);
	}
	else
	{
		vertical_look = sin(data->angle.y) * (data->win.size.y);
		win_size = &data->win.size;
		line_height = set_drawing_limit(data, wall_dist, 4);
		step.y = 1.0 * (line_height / 2 - data->cam.y - vertical_look + *pxl_y);
		step.y /= line_height;
		return (step.y);
	}
}

	void
draw_wall_column(t_data *data, t_int *pxl, t_dbl ray, double wall_dist)
{
	t_img	*wall;
	t_int	wall_pxl;
	int		draw_end;
	double	step;
	int		color;

	wall = get_wall_img(data, &data->piclib, ray);
	draw_end = set_drawing_limit(data, wall_dist, 2);
	step = img_step(data, wall_dist, ray, NULL);
	wall_pxl.x = step * wall->size.x;
	while (pxl->y < draw_end)
	{
		step = img_step(data, wall_dist, ray, &pxl->y);
		wall_pxl.y = step * wall->size.y;
		color = img_color(wall->colors, wall_pxl.x, wall_pxl.y, wall->size);
		put_pixel(&data->win, *pxl, color);
		pxl->y++;
	}
}
