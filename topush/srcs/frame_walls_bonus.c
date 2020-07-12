/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:46:13 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_img
	*get_wall_img(t_data *data, t_piclib *piclib, t_dbl ray)
{
	t_img	*wall;
	double	side;
	t_dbl	cell;

	wall = NULL;
	side = wall_side(data, ray);
	if (side == EA)
		wall = &piclib->ea;
	else if (side == SO)
		wall = &piclib->so;
	else if (side == WE)
		wall = &piclib->we;
	else if (side == NO)
		wall = &piclib->no;
	cell = ray_to_wall(data, ray, dda_step(ray), 0);
	if (data->map[(int)cell.z][(int)cell.x] == STAIRS_DOWN)
		wall = &piclib->s7;
	if (data->map[(int)cell.z][(int)cell.x] == STAIRS_UP)
		wall = &piclib->s8;
	if (data->map[(int)cell.z][(int)cell.x] == ELEVATOR)
		wall = &piclib->s9;
	return (wall);
}

double
	img_step_x(t_data *data, double wall_dist, t_dbl ray, t_dbl cam)
{
	double	step;

	if (!(((int)wall_side(data, ray)) % 2))
		step = wall_dist * ray.z + cam.z;
	else
		step = wall_dist * ray.x + cam.x;
	if (data->skybox[0][0])
	{
		if (ray_orientation(ray) == EA)
			step = -wall_dist * ray.z + cam.z;
		if (ray_orientation(ray) == SO)
			step = -wall_dist * ray.x + cam.x;
	}
	step -= floor(step);
	return (step);
}

double
	img_step(t_data *data, t_dbl cam, t_dbl ray, int *pxl_y)
{
	t_dbl	step;
	double	wall_dist;
	double	line_height;
	int		vertical_look;

	wall_dist = perp_wall_dist(data, cam, ray);
	if (pxl_y == NULL)
	{
		step.x = img_step_x(data, wall_dist, ray, cam);
		return (step.x);
	}
	else
	{
		vertical_look = sin(data->angle.y) * (data->win.size.y);
		line_height = drawing_limit(data, wall_dist, 4);
		step.y = 1.0 * (line_height / 2 - data->cam.y - vertical_look + *pxl_y);
		step.y /= line_height;
		return (step.y);
	}
}

void
	draw_wall_column(t_data *data, t_int *pxl, t_dbl cam, t_dbl ray)
{
	t_img	*wall;
	t_int	wall_pxl;
	double	wall_dist;
	double	step;
	int		color;

	wall = get_wall_img(data, &data->piclib, ray);
	wall_dist = perp_wall_dist(data, cam, ray);
	step = img_step(data, cam, ray, NULL);
	wall_pxl.x = step * wall->size.x;
	while (pxl->y < drawing_limit(data, wall_dist, 2))
	{
		step = img_step(data, cam, ray, &pxl->y);
		wall_pxl.y = step * wall->size.y;
		color = img_color(wall->colors, wall_pxl.x, wall_pxl.y, wall->size);
		put_pixel(&data->win, *pxl, color);
		pxl->y++;
	}
}

	void
draw_walls(t_data *data, t_int *win_size)
{
	t_int	*pxl_ptr;
	t_int	pxl;
	t_dbl	ray;
	double	wall_dist;
	t_dbl	cam;

	cam.x = 1.5;
	cam.z = 1.5;
	if (!data->skybox[0][0])
		cam = data->cam;
	pxl_ptr = &pxl;
	pxl.x = 0;
	while (pxl.x < win_size->x)
	{
		ray = set_ray(data, pxl);
		wall_dist = perp_wall_dist(data, cam, ray);
		data->z_buffer[pxl.x] = wall_dist;
		pxl.y = drawing_limit(data, wall_dist, 0);
		draw_wall_column(data, pxl_ptr, cam, ray);
		pxl.x++;
	}
}
