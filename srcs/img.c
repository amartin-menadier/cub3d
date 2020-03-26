/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/20 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->colors + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	get_texture_img(t_data *data, char *path, t_img *textimg)
{
	textimg->ptr = mlx_xpm_file_to_image(data->mlx, path, &textimg->tw, &textimg->th);
	if (textimg->ptr == NULL)
		close_program(data, "Invalid or missing file at :\n   > ", path);
	textimg->colors = (int*)mlx_get_data_addr(textimg->ptr, &textimg->bits_per_pixel,
			&textimg->line_length, &textimg->endian);
}

int		render_texture(t_data *data, t_img *textimg, int x, int y)
{
	int	x_init;
	int	y_init;

	x_init = x;
	y_init = y;
	while (x < textimg->tw + x_init)
	{
		y = y_init;
		while (y < textimg->th + y_init)
		{
			my_mlx_pixel_put(&data->img, x, y, textimg->colors[y + x]);
			y++;
		}
		x++;
	}
mlx_put_image_to_window(data->mlx, data->win, &data->img, 0, 0);
	return (0);
}
