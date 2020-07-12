/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:44:27 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	draw_sprite_column(t_data *data, t_frame *frame, t_img *img, int stripe)
{
	t_int		spr_img_pos;
	t_settings	*settings;
	int			d;

	spr_img_pos.x = stripe;
	spr_img_pos.y = frame->spr_draw_start.y;
	settings = &data->settings;
	frame->text.x = (int)(256 * fabs(stripe - (-frame->spr_size.x / 2 
		+ frame->spr_screen_x)) * img->size.x / frame->spr_size.x) / 256;
	if (frame->spr_inv.y > 0 && stripe >= 0 && stripe < settings->win_size.x
		&& frame->spr_inv.y < frame->z_buffer[stripe])
	{
		while (spr_img_pos.y < frame->spr_draw_end.y)
		{
			d = (spr_img_pos.y) 
				* 256 - settings->win_size.y * 128 + frame->spr_size.y * 128;
			frame->text.y = ((d * img->size.y) / frame->spr_size.y) / 256;
			if ((img->colors
				[(img->size.y * frame->text.y + frame->text.x)] & 0x00FFFFFF) != 0)
				put_pixel(&data->img, spr_img_pos,
					img->colors[(img->size.y * frame->text.y + frame->text.x)]);
			spr_img_pos.y++;
		}
	}
}

void
	set_sprite_drawing_limits(t_settings *settings, t_frame *frame, int i)
{
	double	inv;
	t_coord	spr_diff;

	spr_diff.x = settings->spr_x[i] - frame->pos.x;
	spr_diff.y = settings->spr_y[i] - frame->pos.y;
	inv = 1.0 / (frame->plane.x * frame->dir.y - frame->dir.x * frame->plane.y);
	frame->spr_inv.x = inv * (frame->dir.y * spr_diff.x - frame->dir.x * spr_diff.y);
	frame->spr_inv.y = inv * (frame->plane.x * spr_diff.y - frame->plane.y * spr_diff.x);
	frame->spr_screen_x = ((settings->win_size.x / 2) * (1 + frame->spr_inv.x / frame->spr_inv.y));
	frame->spr_size.y = abs((int)(settings->win_size.y / (frame->spr_inv.y)));
	frame->spr_draw_start.y = -frame->spr_size.y / 2 + settings->win_size.y / 2;
	if (frame->spr_draw_start.y < 0)
		frame->spr_draw_start.y = 0;
	frame->spr_draw_end.y = frame->spr_size.y / 2 + settings->win_size.y / 2;
	if (frame->spr_draw_end.y >= settings->win_size.y)
		frame->spr_draw_end.y = settings->win_size.y;
	frame->spr_size.x = abs((int)(settings->win_size.y / (frame->spr_inv.y)));
	frame->spr_draw_start.x = -frame->spr_size.x / 2 + frame->spr_screen_x - 1;
	if (frame->spr_draw_start.x < 0)
		frame->spr_draw_start.x = 0;
	frame->spr_draw_end.x = frame->spr_size.x / 2 + frame->spr_screen_x + 1;
	if (frame->spr_draw_end.x > settings->win_size.x)
		frame->spr_draw_end.x = settings->win_size.x;
}

void
	draw_sprites
		(t_data *data, t_settings *settings, t_frame *frame, t_img *text)
{
	int	i;
	int	j;
	int	stripe;

	i = 0;
	j = 0;
	while (i < settings->spr_count || j < settings->spr_count)
	{
		if (j == frame->spr_order[i] && frame->spr_dist[i] > 0.1)
		{
			set_sprite_drawing_limits(settings, frame, i);
			stripe = frame->spr_draw_start.x;
			while (stripe < frame->spr_draw_end.x)
			{
				draw_sprite_column(data, frame, text, stripe);
				stripe++;
			}
			j++;
			i = -1;
		}
		i++;
	}
}

void
	init_sprite_order(t_settings *settings, t_frame *frame)
{
	int i;

	i = 0;
	while (i < settings->spr_count && !frame->spr_sorted)
	{
		frame->spr_order[i] = i;
		frame->spr_dist[i] =
			((frame->pos.x - settings->spr_x[i]) * (frame->pos.x - settings->spr_x[i])
			+ (frame->pos.y - settings->spr_y[i]) * (frame->pos.y - settings->spr_y[i]));
		i++;
	}
}

void
	sort_sprites(t_settings *settings, t_frame *frame)
{
	t_int	at;
	int		tmp_order;

	init_sprite_order(settings, frame);
	at.x = 0;
	while (at.x < settings->spr_count - 1)
	{
		at.z = 0;
		at.y = at.x;
		while (++at.y < settings->spr_count)
		{
			if ((frame->spr_dist[at.x] < frame->spr_dist[at.y]
				&& frame->spr_order[at.x] < frame->spr_order[at.y])
				|| (frame->spr_dist[at.x] > frame->spr_dist[at.y]
				&& frame->spr_order[at.x] > frame->spr_order[at.y]))
			{
				at.z++;
				tmp_order = frame->spr_order[at.x];
				frame->spr_order[at.x] = frame->spr_order[at.y];
				frame->spr_order[at.y] = tmp_order;
			}
		}
		at.x = (at.z == 0) ? at.x + 1 : at.x;
	}
	frame->spr_sorted++;
}
