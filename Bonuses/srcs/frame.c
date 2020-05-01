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

	void
draw_life_string(t_data *data)
{
	char	*value;
	t_int	ctr;

	ctr.x = lifebar_data(data, CENTER_X);
	ctr.y = lifebar_data(data, CENTER_Y);
	value = ft_itoa(data->set.life);
	mlx_string_put(data->mlx, data->window, ctr.x, ctr.y, BLACK, value);
	free(value);
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

// 0 SO NO 1 EA WE
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

/*
 ** DDA = Digital Differential Analyser
 */

	t_dbl
get_delta_dist(t_dbl ray)
{
	t_dbl	delta_dist;

	if (ray.x == 0)
		delta_dist.y = 0;
	else if (ray.y == 0)
		delta_dist.y = 1;
	else
		delta_dist.y = fabs(1 / ray.y);
	if (ray.y == 0)
		delta_dist.x = 0;
	else if (ray.x == 0)
		delta_dist.x = 1;
	else
		delta_dist.x = fabs (1 / ray.x);
return (delta_dist);
}


	t_dbl
get_side_dist(t_dbl delta_dist, t_dbl pos, t_dbl ray)
{
	t_dbl	cell;
	t_dbl	side_dist;

	cell.x = (int)pos.x;
	cell.y = (int)pos.y;
	if (ray.x < 0)
		side_dist.x = (pos.x - cell.x) * delta_dist.x;
	else
		side_dist.x = (cell.x + 1.0 - pos.x) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos.y - cell.y) * delta_dist.y;
	else
		side_dist.y = (cell.y + 1.0 - pos.y) * delta_dist.y;
	return (side_dist);
}

	t_dbl
get_DDA_step(t_dbl ray)
{
	t_dbl	step;

	if (ray.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

	t_dbl
get_hit_wall(t_data data, t_dbl ray, t_dbl step, int mod)
{
	t_dbl	cell;
	t_dbl	delta_dist;
	t_dbl	side_dist;
	t_dbl	side;

	delta_dist = get_delta_dist(ray);
	side_dist = get_side_dist(delta_dist, data.set.pos, ray);
	cell.x = (int)data.set.pos.x;
	cell.y = (int)data.set.pos.y;
	while (data.set.map[(int)cell.y][(int)cell.x] != WALL)
	{
		if(side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			cell.x += step.x;
			side.x = (ray.x > 0 ? EA : WE);
		}
		else
		{
			side_dist.y += delta_dist.y;
			cell.y += step.y;
			side.x = (ray.y > 0 ? NO : SO);
		}
	}
	return (mod == 0 ? cell : side);
}

	double
perform_DDA(t_data *data, t_dbl pos, t_dbl ray, int mod)
{
	t_dbl	step;
	t_dbl	hit_wall;
	double	perp_wall_dist;
	t_dbl	side;

	step = get_DDA_step(ray);
	hit_wall = get_hit_wall(*data, ray, step, 0);
	side = get_hit_wall(*data, ray, step, 1);
	if(side.x == EA || side.x == WE)
		perp_wall_dist = (hit_wall.x - pos.x + (1 - step.x) / 2) / ray.x;
	else
		perp_wall_dist = (hit_wall.y - pos.y + (1 - step.y) / 2) / ray.y;
//	data->set.side = side.x;
//	data->set.perp_wall_dist = perp_wall_dist;
	if (data->skybox)
		perp_wall_dist = 1;
	if (mod == 0)
		return (perp_wall_dist);
	else
		return (side.x);
}

	t_dbl
set_ray(t_data *data, t_set *set, t_int scr)
{
	double	camera_x;
	t_dbl	ray;
	t_dbl	plane;

	camera_x = 2.0 * scr.x /data->set.win_size.x - 1;
	if (data->skybox)
	{
//		ray.x = cos(set->angle - (PI / 4) * camera_x);
//		ray.y = sin(set->angle - (PI / 4) * camera_x);
	//	ray = coord_from_angle(set->angle - (PI / 4) * camera_x, NULL);
		ray = rotate_point(set->angle - (PI / 4) * camera_x, NULL, NULL);
	}
	else
	{
		plane = rotate_point(set->angle - PI / 2, NULL, NULL);
		ray = rotate_point(set->angle , NULL, NULL);
		ray.x += plane.x * camera_x;
		ray.y += plane.y * camera_x;
//		ray.x = set->dir.x + set->plan.x * camera_x;
//		ray.y = set->dir.y + set->plan.y * camera_x;
	}
	return(ray);
}

	void
ray_cast(t_data *data, t_int win_size, int skybox)
{
	t_int	scr;
	t_dbl	ray;
	double	perp_wall_dist;

	scr.x = 0;
	while (scr.x < data->set.win_size.x)
	{
		ray = set_ray(data, &data->set, scr);
		perp_wall_dist = perform_DDA(data, data->set.pos, ray, 0);
		data->set.z_buffer[scr.x] = perp_wall_dist;
		scr.y = set_drawing_limit(win_size, perp_wall_dist, skybox);
		if (!skybox)
		{
			draw_wall_column(data, scr, ray, perp_wall_dist);
		}
		else
		{
			draw_skybox_column(data, scr, ray, perp_wall_dist);
		}
		scr.x++;
	}
}

	int
render_next_frame(t_data *data)
{
	if (data->set.life > 0 && data->set.frame_done == 0)
	{
		draw_floor_and_sky(data, data->set.angle, data->set.win_size);
		ray_cast(data, data->set.win_size, data->skybox);
		draw_sprites(data, data->piclib, &data->set);
		draw_interface(data, &data->piclib, &data->set);
		mlx_put_image_to_window(data->mlx, data->window, data->scr.ptr, 0, 0);
		draw_life_string(data);
		if (data->save == 1)
			create_bmp(data, &data->scr, "start.bmp");
		data->set.frame_done = 1;
	}
	return (0);
}

