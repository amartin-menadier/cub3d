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

/*
** in set_drawing_limit, odd mods (so mod % 2 is true) are for skyboxes
*/

	int
set_drawing_limit(t_data *data, double wall_dist, int mod)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		vertical_look;

	vertical_look = sin(data->angle.y) * (data->win.size.y);
	line_height = fabs(data->win.size.y / wall_dist);
	if (mod % 2)
		line_height = data->win.size.x;
	draw_start = vertical_look + data->cam.y - line_height / 2;
	draw_end = vertical_look + data->cam.y + line_height / 2;
	if ((mod == 0 || mod == 1) && draw_start < 0)
		return (0);
	else if (mod == 0 || mod == 1)
		return (draw_start);
	else if ((mod == 2 || mod == 3) && draw_end > data->win.size.y)
		return (data->win.size.y);
	else if (mod == 2 || mod == 3)
		return (draw_end);
	else if (mod == 4 || mod == 5)
		return (line_height);
	else
		return (-100000000);
}

	t_dbl
set_ray(t_data *data, t_int win)
{
	double	camera_x;
	t_dbl	ray;
	t_dbl	plane;

	camera_x = 2.0 * win.x / data->win.size.x - 1;
	if (data->skybox)
	{
		ray = rotate_point(data->angle.x - (PI / 3) * camera_x, NULL, NULL);
	}
	else
	{
		plane = rotate_point(data->angle.x - PI / 2, NULL, NULL);
		ray = rotate_point(data->angle.x , NULL, NULL);
		ray.x += plane.x * camera_x;
		ray.z += plane.z * camera_x;
	}
	return(ray);
}

	void
draw_walls(t_data *data, t_int *win_size, int skybox)
{
	t_int	*pxl_ptr;
	t_int	pxl;
	t_dbl	ray;
	double	wall_dist;

	pxl_ptr = &pxl;
	pxl.x = 0;
	while (pxl.x < win_size->x)
	{
		ft_putstr_fd("\nframe11", 1);
		ray = set_ray(data, pxl);
		ft_putstr_fd("\nframe12", 1);
		wall_dist = perform_DDA(data, data->cam, ray, 0);
		ft_putstr_fd("\nframe13", 1);
		data->z_buffer[pxl.x] = wall_dist;
		ft_putstr_fd("\nframe14", 1);
		pxl.y = set_drawing_limit(data, wall_dist, skybox);
		ft_putstr_fd("\nframe15", 1);
		if (!skybox)
		{
			draw_wall_column(data, pxl_ptr, ray, wall_dist);
		}
		else
		{
			draw_skybox_column(data, pxl_ptr, ray, wall_dist);
		}
		pxl.x++;
	}
}

	int
render_next_frame(t_data *data)
{
	hook_event(data);
	while (data->life > 0 && data->frame_done == 0)
	{
		ft_putstr_fd("\nframe1", 1);
		draw_floor_and_sky(data, data->angle, data->win.size);
		ft_putstr_fd("\nframe2", 1);
		draw_walls(data, &data->win.size, data->skybox);
		ft_putstr_fd("\nframe3", 1);
		if (!data->skybox)
			draw_sprites(data, &data->piclib);
		ft_putstr_fd("\nframe4", 1);
		draw_interface(data, &data->piclib);
		ft_putstr_fd("\nframe5", 1);
		mlx_put_image_to_window(data->mlx, data->window, data->win.ptr, 0, 0);
		draw_life_string(data);
		if (data->save == 1)
			create_bmp(data, &data->win, "start.bmp");
		data->frame_done = 1;
	}
	return (0);
}

