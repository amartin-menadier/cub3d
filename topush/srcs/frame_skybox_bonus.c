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

#include "cub3d_bonus.h"

	double
ray_orientation(t_dbl ray)
{
	double	orientation;

	if (ray.z > 0 && fabs(ray.x) < fabs(ray.z))
		orientation = NO;
	else if (ray.x > 0 && fabs(ray.x) > fabs(ray.z))
		orientation = EA;
	else if (ray.z < 0 && fabs(ray.x) < fabs(ray.z))
		orientation = SO;
	else if (ray.x < 0 && fabs(ray.x) > fabs(ray.z))
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
	orientation = ray_orientation(ray);
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

/*
** the while is cheating to fix a bug but it seems to work
*/
	t_int
get_skybox_pixel(t_data *data, int pxl_y, t_dbl ray, t_img *face)
{
	t_int	face_pxl;
	int		orientation;
	t_dbl	ratio;
	int		cam_height;
	int		line_height;

	orientation = ray_orientation(ray);
	if (orientation == NO)
		ratio.x = (0.5 + ray.x / sqrt(2));
	else if (orientation == EA)
		ratio.x = (0.5 - ray.z / sqrt(2));
	else if (orientation == SO)
		ratio.x = (0.5 - ray.x / sqrt(2));
	else if (orientation == WE)
		ratio.x = (0.5 + ray.z / sqrt(2));
	face_pxl.x = ratio.x * face->size.x;
	while (face_pxl.x >= face->size.x)
		face_pxl.x--;
	line_height = drawing_limit(data, 1, 5);//try PWD 0.5 instead of 1
	cam_height = data->cam.y + sin(data->angle.y) * data->win.size.y;
	ratio.y = 1.00 * (line_height / 2 - cam_height + pxl_y) / line_height;
	face_pxl.y = ratio.y * face->size.y;
	return(face_pxl);
}

/*
** The second while is unecessary and just there to fix mountain.xpm bug => find another and proper skybox is needed
*/
	void
draw_skybox_column(t_data *data, t_int *pxl, t_dbl ray, double wall_dist)
{
	t_img	*face;
	t_int	face_pxl;
	int		color;
	int		draw_end;
	t_int	*win_size;

	win_size = &data->win.size;
	face = get_skybox_face(&data->piclib, ray);
	draw_end = drawing_limit(data, wall_dist, 3);
	while (pxl->y < draw_end)
	{
		face_pxl = get_skybox_pixel(data, pxl->y, ray, face);
		color = img_color(face->colors, face_pxl.x, face_pxl.y, face->size);
		while (color > WHITE - 0x222222)
		{
			face_pxl.y++;
			color = img_color(face->colors, face_pxl.x, face_pxl.y, face->size);
		}
		put_pixel(&data->win, *pxl, color);
		pxl->y++;
	}
}

	void
draw_skybox(t_data *data, t_int *win_size)
{
	t_int	*pxl_ptr;
	t_int	pxl;
	t_dbl	ray;
	double	wall_dist;

	pxl_ptr = &pxl;
	pxl.x = 0;
//	draw_floor_and_sky(data, data->angle, data->win.size);
//	useless ? 
	wall_dist = fmax(win_size->x, win_size->y) / win_size->y;
	while (pxl.x < win_size->x)
	{
		ray = set_ray(data, pxl);
		data->z_buffer[pxl.x] = wall_dist;
		pxl.y = drawing_limit(data, wall_dist, 1);
		draw_skybox_column(data, pxl_ptr, ray, wall_dist);
		pxl.x++;
	}
}
