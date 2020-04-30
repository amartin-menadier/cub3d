/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
sprite_hit(t_data *data)
{
	t_int	pos;
	char	case_value;
	
	pos.x = (int)data->set.pos.x;
	pos.y = (int)data->set.pos.y;
	case_value = data->set.map[pos.y][pos.x];
	if (case_value == '3' && data->set.life == 100)
		return;
	if (case_value == '2')
		data->set.life -= 19;
	if (data->set.life <= 0)
		game_over(data);
	if (case_value == '3')
		data->set.life += 20;
	if (data->set.life > 100)
		data->set.life = 100;
	data->set.map[pos.y][pos.x] = '0';
	data->set.spr_count--;
	free(data->set.spr);
	data->set.spr = NULL;
	get_sprites_data(data, &data->set, data->set.map);
}

	void
set_sprite_drawing_limits(t_set *set, int i)
{
	double	inv;
	t_dbl	spr_diff;
	t_dbl	dir;
	t_dbl	plane;
//	t_dbl	spr_inv;

	t_set	*S;
	S = set;

	dir = rotate_point(set->angle, NULL, NULL);
	plane = rotate_point(set->angle - PI / 2, NULL, NULL);

	spr_diff.x = S->spr[i].x - S->pos.x;
	spr_diff.y = S->spr[i].y - S->pos.y;
	inv = 1.0 / (plane.x * dir.y - dir.x * plane.y);
//	S->spr_inv.x = inv * (S->dir.y * spr_diff.x - S->dir.x * spr_diff.y);
//	S->spr_inv.y = inv * (S->plane.x * spr_diff.y - S->plane.y * spr_diff.x);

S->spr_inv.x = inv * (dir.y * spr_diff.x - dir.x * spr_diff.y);
	S->spr_inv.y = inv * (plane.x * spr_diff.y - plane.y * spr_diff.x);
	S->spr_screen_x = ((S->win_size.x / 2) * (1 + S->spr_inv.x / S->spr_inv.y));
	S->spr_size.y = abs((int)(S->win_size.y / (S->spr_inv.y)));
	
	S->spr_draw_start.y = -S->spr_size.y / 2 + S->win_size.y / 2;
	if(S->spr_draw_start.y < 0) 
		S->spr_draw_start.y = 0;
	S->spr_draw_end.y = S->spr_size.y / 2 + S->win_size.y / 2;
	if(S->spr_draw_end.y >= S->win_size.y)
		S->spr_draw_end.y = S->win_size.y;
	S->spr_size.x = abs((int)(S->win_size.x / (2 * S->spr_inv.y)));
//	S->spr_size.x = abs((int)(S->win_size.y / (S->spr_inv.y)));
	S->spr_draw_start.x = -S->spr_size.x / 2 + S->spr_screen_x;
	if(S->spr_draw_start.x < 0) 
		S->spr_draw_start.x = 0;
	S->spr_draw_end.x = S->spr_size.x / 2 + S->spr_screen_x;
	if(S->spr_draw_end.x > S->win_size.x)
		S->spr_draw_end.x = S->win_size.x;
}

	int
sprite_player_same_case(t_set *set, int i)
{
	t_int	spr;
	t_int	player;

	spr.x = (int)set->spr[i].x;
	spr.y = (int)set->spr[i].y;
	player.x = (int)set->pos.x;
	player.y = (int)set->pos.y;

	if (spr.x == player.x && spr.y == player.y)
		return (1);
	else
		return (0);
}

	double
dist(t_dbl pos, t_dbl obj)
{
	double	dist;

	dist = hypot((pos.x - obj.x), (pos.y - obj.y));
	return (dist);
}

	void
sort_sprites(t_dbl pos, t_dbl *spr, int spr_count)
{
	int		i;
	int		j;
	int		k;
	t_dbl	tmp_spr;

	i = 0;
	while (i < spr_count - 1)
	{
		k = 0;
		j = i;
		while (++j < spr_count)
		{
		if ((dist(pos, spr[i]) < dist(pos, spr[j]) && i < j)
				|| (dist(pos, spr[i]) > dist(pos, spr[j]) && i > j))
			{
				k++;
				tmp_spr = spr[i];
				spr[i] = spr[j];
				spr[j] = tmp_spr;
			}
		}
		i = (k == 0) ? i + 1 : i;
	}
}

	void
draw_sprite_column(t_data *data, t_img spr, t_int scr)
{
	t_int		spr_pxl;

	t_set *S;
	S = &data->set;

	scr.y = S->spr_draw_start.y;
	spr_pxl.x = (int)(256 * fabs(scr.x - (-S->spr_size.x / 2 
					+ S->spr_screen_x)) * spr.size.x / S->spr_size.x) / 256;

	if (S->spr_inv.y > 0 && scr.x >= 0 && scr.x < S->win_size.x
			&& S->spr_inv.y < S->z_buffer[scr.x])
	{
		while (scr.y < S->spr_draw_end.y)
		{
int		d;
int		color;
			d = (scr.y) * 256 - S->win_size.y * 128 + S->spr_size.y * 128;

			spr_pxl.y = ((d * spr.size.y) / S->spr_size.y) / 256;
//			spr_pxl.y = get_sprite_pixel();
			if (!(color = get_error_color(spr_pxl.x, spr_pxl.y, spr.size)))
				color = spr.colors[spr_pxl.y * spr.size.x + spr_pxl.x];
			if (color != BLACK)
				put_pixel(&data->scr, scr, color);
			scr.y++;
		}
	}
}

	void
draw_sprites(t_data *data, t_piclib lib, t_set *set)
{
	int		i;
	t_int	scr;
	t_img	img;

	sort_sprites(set->pos, set->spr, set->spr_count);
	i = 0;
	while (i < set->spr_count)
	{
		set_sprite_drawing_limits(set, i);
		scr.x = set->spr_draw_start.x;
		img = get_sprite_image(set->map, set->spr[i], lib);
		while (scr.x < set->spr_draw_end.x)
		{
			if (!(sprite_player_same_case(set, i)))
				draw_sprite_column(data, img, scr);
			scr.x++;
		}
		i++;
	}
}
