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
 ** DDA = Digital Differential Analyser
 */

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
draw_walls(t_data *data, t_int win_size, int skybox)
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
		draw_walls(data, data->set.win_size, data->skybox);
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

