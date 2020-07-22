/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/22 15:23:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	render_next_frame(t_data *data)
{
	int		x;
	t_img	*text_img;

	x = 0;
	mlx_destroy_image(data->mlx, data->img.ptr);
	data->img.ptr = mlx_new_image(data->mlx, data->settings.win_size.x,
			data->settings.win_size.y);
	while (x < data->settings.win_size.x)
	{
		set_ray(data, &data->frame, x);
		perform_dda(data, &data->frame);
		data->frame.z_buffer[x] = data->frame.perp_wall_dist;
		set_drawing_limits(data, &data->frame);
		text_img = get_texture_img(&data->frame);
		draw_column(data, &data->frame, text_img, x);
		x++;
	}
	draw_sprites(data, &data->settings, &data->frame, &data->frame.s_img);
	if (data->save)
	{
		create_bmp(data, &data->img, "start.bmp");
		close_program(data, "First image of the game saved ", "\\o/\n");
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}

void
	draw_column(t_data *data, t_frame *frame, t_img *text_img, int x)
{
	t_int	pos;
	double	step;
	double	tex_pos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < frame->draw_start)
	{
		put_pixel(&data->img, pos, data->settings.ceiling_color);
		pos.y++;
	}
	step = 1.0 * text_img->size.y / frame->line_height;
	tex_pos = (frame->draw_start - data->settings.win_size.y / 2 +
		frame->line_height / 2) * step;
	while (pos.y < frame->draw_end)
	{
		frame->text.y = (int)tex_pos & (text_img->size.y - 1);
		tex_pos += step;
		put_pixel(&data->img, pos, text_img->colors
			[(text_img->size.y * frame->text.y + frame->text.x)]);
		pos.y++;
	}
	pos.y--;
	while (pos.y++ < data->settings.win_size.y)
		put_pixel(&data->img, pos, data->settings.floor_color);
}

void
	set_drawing_limits(t_data *data, t_frame *frame)
{
	frame->line_height =
		abs((int)(data->settings.win_size.y / (frame->perp_wall_dist)));
	frame->draw_start = -frame->line_height / 2 + data->settings.win_size.y / 2;
	if (frame->draw_start < 0)
		frame->draw_start = 0;
	frame->draw_end = frame->line_height / 2 + data->settings.win_size.y / 2;
	if (frame->draw_end >= data->settings.win_size.y)
		frame->draw_end = data->settings.win_size.y;
	if (frame->side == 0)
		frame->wall_x = frame->pos.y + frame->perp_wall_dist * frame->ray.y;
	else
		frame->wall_x = frame->pos.x + frame->perp_wall_dist * frame->ray.x;
	frame->wall_x -= floor((frame->wall_x));
}
