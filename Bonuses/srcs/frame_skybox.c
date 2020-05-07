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

	if (ray.z > 0 && fabs(ray.x) < fabs(ray.z))
		orientation = NO;
	else if (ray.x > 0 && fabs(ray.x) >= fabs(ray.z))
		orientation = EA;
	else if (ray.z < 0 && fabs(ray.x) < fabs(ray.z))
		orientation = SO;
	else if (ray.x < 0 && fabs(ray.x) >= fabs(ray.z))
		orientation = WE;
	else
		return (-1);
	return (orientation);
}

	t_img
*get_skybox_face(t_piclib *piclib, t_dbl ray)
{
	t_img	*face;
	int		orientation;

	face = NULL;
	orientation = get_orientation(ray);
	if (orientation == EA)
		face = &piclib->ea;
	else if (orientation == SO)
		face = &piclib->so;
	else if (orientation == WE)
		face = &piclib->we;
	else if (orientation == NO)
		face = &piclib->no;
	else
		face->ptr = NULL;
	return (face);
}

	t_int
get_skybox_pixel(t_data *data, int pxl_y, t_dbl ray, t_img *face)
{
	t_int	face_pxl;
	int		orientation;
	t_dbl	ratio;
	int		cam_height;
	int		line_height;

	orientation = get_orientation(ray);
	if (orientation == NO)
		ratio.x = (0.5 + ray.x / sqrt(2));
	else if (orientation == EA)
		ratio.x = (0.5 - ray.z / sqrt(2));
	else if (orientation == SO)
		ratio.x = (0.5 - ray.x / sqrt(2));
	else if (orientation == WE)
		ratio.x = (0.5 + ray.z / sqrt(2));
	else
		ratio.x = - 1 / face->size.x;
	face_pxl.x = ratio.x * face->size.x;
	if (face_pxl.x < 0 || face_pxl.x >= face->size.x)
		face_pxl.x = -1;
	line_height = set_drawing_limit(data, 1, 5);//try PWD 0.5 instead of 1
	cam_height = data->cam.y + sin(data->angle.y) * data->win.size.y;
	ratio.y = 1.00 * (line_height / 2 - cam_height + pxl_y) / line_height;
	face_pxl.y = ratio.y * face->size.y;
	return(face_pxl);
}

	void
draw_skybox_column(t_data *data, t_int *pxl, t_dbl ray, double perp_wall_dist)
{
	t_img	*face;
	t_int	face_pxl;
	int		color;
	int		draw_end;
	t_int	*win_size;

	win_size = &data->win.size;
	face = get_skybox_face(&data->piclib, ray);
	draw_end = set_drawing_limit(data, perp_wall_dist, 3);
	while (pxl->y < draw_end)
	{
		face_pxl = get_skybox_pixel(data, pxl->y, ray, face);
		color = img_color(face->colors, face_pxl.x, face_pxl.y, face->size);
		put_pixel(&data->win, *pxl, color);
		pxl->y++;
	}
}
