/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:19 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
create_piclib(t_data *data, t_piclib *piclib)
{
	create_img(data, piclib->ea.path, &piclib->ea);
	create_img(data, piclib->so.path, &piclib->so);
	create_img(data, piclib->we.path, &piclib->we);
	create_img(data, piclib->no.path, &piclib->no);
	create_img(data, piclib->flr.path, &piclib->flr); 
	create_img(data, piclib->sky.path, &piclib->sky); 
	create_img(data, piclib->s2.path, &piclib->s2); 
	create_img(data, piclib->s3.path, &piclib->s3); 
	create_img(data, piclib->no.path, &piclib->skybox);
	create_img(data, "./textures/intellolcut.xpm", &piclib->avatar);
	create_img(data, "./textures/gameover.xpm", &piclib->game_over);
	create_img(data, "./textures/civ_mask.xpm", &piclib->mask);
	if (data->skybox)
		create_skybox(data, piclib, &piclib->skybox);
}

	void
set_mlx(t_data *data, t_img *scr, t_int win_size)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	scr->ptr = mlx_new_image(data->mlx, win_size.x, win_size.y);
	scr->colors = (int *)mlx_get_data_addr(scr->ptr, &scr->bpp,
			&scr->line_length, &scr->endian);
	scr->size.x = win_size.x;
	scr->size.y = win_size.y;
}

	void
set_game(t_data *data, t_set *set)
{
	parse_cub_file(data);
	set_mlx(data, &data->scr, data->set.win_size);
	create_piclib(data, &data->piclib);
	if (!(set->z_buffer = malloc(sizeof(double *) * set->win_size.x)))
		close_program(data, "Failed allocating z_buffer while", "set_game");
}
