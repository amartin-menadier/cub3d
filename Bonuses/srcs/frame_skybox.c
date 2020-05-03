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

	int
get_orientation(t_dbl ray)
{
	int	orientation;

	if (ray.y > 0 && fabs(ray.x) < fabs(ray.y))
		orientation = NO;
	else if (ray.x > 0 && fabs(ray.x) >= fabs(ray.y))
		orientation = EA;
	else if (ray.y < 0 && fabs(ray.x) < fabs(ray.y))
		orientation = SO;
	else if (ray.x < 0 && fabs(ray.x) >= fabs(ray.y))
		orientation = WE;
	else
		return (-1);
	return (orientation);
}

	t_img
get_skybox_face(t_piclib *piclib, t_dbl ray)
{
	t_img	face;
	int		orientation;

	orientation = get_orientation(ray);
	if (orientation == EA)
		face = piclib->ea;
	else if (orientation == SO)
		face = piclib->so;
	else if (orientation == WE)
		face = piclib->we;
	else if (orientation == NO)
		face = piclib->no;
	else
		face.ptr = NULL;
	return (face);
}

	t_int
get_skybox_pixel(t_int win_size, int scr_y, t_dbl ray, t_img face)
{
	t_int	face_pxl;
	int		orientation;
	t_dbl	ratio;
	int		line_height;

	orientation = get_orientation(ray);
	if (orientation == NO)
		ratio.x = (0.5 + ray.x / sqrt(2));
	else if (orientation == EA)
		ratio.x = (0.5 - ray.y / sqrt(2));
	else if (orientation == SO)
		ratio.x = (0.5 - ray.x / sqrt(2));
	else if (orientation == WE)
		ratio.x = (0.5 + ray.y / sqrt(2));
	else
		ratio.x = - 1 / face.size.x;
	face_pxl.x = ratio.x * face.size.x;
	if (face_pxl.x < 0 || face_pxl.x >= face.size.x)
		face_pxl.x = -1;
	line_height = set_drawing_limit(win_size, 1, 5);//try PWD 0.5 instead of 1
	ratio.y = 1.00 * ((line_height - win_size.y) / 2 + scr_y) / line_height;
	face_pxl.y = ratio.y * face.size.y;
	if (face_pxl.y < 0 || face_pxl.y >= face.size.y)
		face_pxl.y = -1;
	return(face_pxl);
}

	void
draw_skybox_column(t_data *data, t_int scr, t_dbl ray, double perp_wall_dist)
{
	t_img	face;
	t_int	face_pxl;
	int		color;
	int		draw_end;

	face = get_skybox_face(&data->piclib, ray);
	draw_end = set_drawing_limit(data->set.win_size, perp_wall_dist, 3);
	while (scr.y < draw_end)
	{
		face_pxl = get_skybox_pixel(data->set.win_size, scr.y, ray, face);
		color = get_img_color(face, face_pxl.x, face_pxl.y, face.size);
		put_pixel(&data->scr, scr, color);
		scr.y++;
	}
}

	int
set_drawing_limit(t_int win_size, double perp_wall_dist, int mod)
{
	int		line_height;
	int		draw_start;
	int		draw_end;

	line_height = fabs(win_size.y / perp_wall_dist);
	if (mod % 2)
		line_height = win_size.x;
	draw_start = (win_size.y - line_height) / 2;
	draw_end = win_size.y / 2 + line_height / 2;
	if ((mod == 0 || mod == 1) && draw_start < 0)
		return (0);
	else if (mod == 0 || mod == 1)
		return (draw_start);
	else if ((mod == 2 || mod == 3) && draw_end > win_size.y)
		return (win_size.y);
	else if (mod == 2 || mod == 3)
		return (draw_end);
	else if (mod == 4 || mod == 5)
		return (line_height);
	else
		return (-100000000);
}
