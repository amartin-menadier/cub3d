/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:07:21 by amenadier         #+#    #+#             */
/*   Updated: 2020/07/12 18:03:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	put_pixel(t_img *img, t_int pos, int color)
{
	char	*dst;

	dst = (char *)img->colors
		+ (pos.y * img->line_length + pos.x * (img->bpp / 8));
	*(int*)dst = color;
}

void
	create_texture_img(t_data *data, char *path, t_img *text)
{
	text->ptr =
		mlx_xpm_file_to_image(data->mlx, path, &text->size.x, &text->size.y);
	if (text->ptr == NULL)
		close_program(data, "Invalid or missing texture at :\n   > ", path);
	text->colors = (int*)mlx_get_data_addr(text->ptr, &text->bpp,
			&text->line_length, &text->endian);
}
