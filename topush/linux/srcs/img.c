/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:07:21 by amenadier         #+#    #+#             */
/*   Updated: 2020/07/21 19:52:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_int
	check_texture_pxl(t_int text, t_int img_size)
{
	t_int		ret;

	ret.x = text.x;
	ret.y = text.y;
	if (ret.x < 0)
		ret.x = 0;
	if (ret.y < 0)
		ret.y = 0;
	if (ret.x >= img_size.x)
		ret.x = img_size.x - 1;
	if (ret.y >= img_size.y)
		ret.y = img_size.y - 1;
	return (ret);
}

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
