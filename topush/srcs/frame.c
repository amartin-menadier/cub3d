/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:47:06 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	render_next_frame(t_data *data)
{
	int		x;
	t_img	*text_img;

	x = 0;
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
	sort_sprites(&data->settings, &data->frame);
	draw_sprites(data, &data->settings, &data->frame, &data->frame.s_img);
	if (data->save == 1)
	{
		create_bmp(data, &data->img, "start.bmp");
		close_program(data, "First image of the game saved ", "\\o/\n");
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	return (0);
}

void
	draw_column(t_data *data, t_frame *frame, t_img *text_img, int x)
{
	t_int	pos;
	double	step;
	double	texPos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < frame->draw_start)
	{
		put_pixel(&data->img, pos, data->settings.ceiling_color);
		pos.y++;
	}
	step = 1.0 * text_img->size.y / frame->line_height;
	texPos = (frame->draw_start - data->settings.win_size.y / 2 +
		frame->line_height / 2) * step;
	while (pos.y < frame->draw_end)
	{
		frame->text.y = (int)texPos & (text_img->size.y - 1);
		texPos += step;
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

/*
** dda = Digital Differential Analyser
*/

void
	perform_dda(t_data *data, t_frame *frame)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (frame->side_dist.x < frame->side_dist.y)
		{
			frame->side_dist.x += frame->delta_dist.x;
			frame->map.x += frame->step.x;
			frame->side = 0;
		}
		else
		{
			frame->side_dist.y += frame->delta_dist.y;
			frame->map.y += frame->step.y;
			frame->side = 1;
		}
		if (data->settings.map[(int)frame->map.y][(int)frame->map.x] == '1')
			hit = 1;
	}
	if (frame->side == 0)
		frame->perp_wall_dist = (frame->map.x - frame->pos.x + (1 - frame->step.x)/2)/ frame->ray.x;
	else
		frame->perp_wall_dist = (frame->map.y - frame->pos.y + (1 - frame->step.y)/2)/ frame->ray.y;
}

void
	set_ray(t_data *data, t_frame *frame, int x)
{
	frame->map.x = (int)frame->pos.x;
	frame->map.y = (int)frame->pos.y;
	frame->camera_x = 2 * x /(double)data->settings.win_size.x - 1;
	frame->ray.x = frame->dir.x + frame->plane.x * frame->camera_x;
	frame->ray.y = frame->dir.y + frame->plane.y * frame->camera_x;
	frame->delta_dist.x =
		(frame->ray.y == 0) ? 0 : ((frame->ray.x == 0) ? 1 : fabs(1 / frame->ray.x));
	frame->delta_dist.y =
		(frame->ray.x == 0) ? 0 : ((frame->ray.y == 0) ? 1 : fabs(1 / frame->ray.y));
	if (frame->ray.x < 0)
		frame->step.x = -1;
	else
		frame->step.x = 1;
	if (frame->ray.y < 0)
		frame->step.y = -1;
	else
		frame->step.y = 1;
	if (frame->ray.x < 0)
		frame->side_dist.x = (frame->pos.x - frame->map.x) * frame->delta_dist.x;
	else
		frame->side_dist.x = (frame->map.x + 1.0 - frame->pos.x) * frame->delta_dist.x;
	if (frame->ray.y < 0)
		frame->side_dist.y = (frame->pos.y - frame->map.y) * frame->delta_dist.y;
	else
		frame->side_dist.y = (frame->map.y + 1.0 - frame->pos.y) * frame->delta_dist.y;
}
