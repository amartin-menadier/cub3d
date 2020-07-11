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

#include "cub3d_bonus.h"

	int
render_next_frame(t_data *data)
{
	hook_event(data);
	while (data->life > 0 && data->frame_done == 0)
	{
		if (data->skybox[0][0] < 0)
			draw_skybox(data, &data->win.size);
		else
		{
			draw_floor_and_sky(data, data->angle, data->win.size);
			draw_walls(data, &data->win.size);
			draw_sprites(data, &data->piclib);
		}
		draw_interface(data, &data->piclib);
		mlx_put_image_to_window(data->mlx, data->window, data->win.ptr, 0, 0);
		draw_life_string(data);
		if (data->save == 1)
			create_bmp(data, &data->win, "start.bmp");
		data->frame_done = 1;
	}
	if (!ft_strncmp(data->cub_path, "./cub/bonus/42_start1.cub", 25))
		draw_script(data, DRAW_START);
	if (!ft_strncmp(data->cub_path, "./cub/bonus/skybox.cub", 22))
		draw_script(data, SKYBOX);
	return (0);
}
