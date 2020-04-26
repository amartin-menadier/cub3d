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

	void
put_pixel(t_img *img, t_int pos, int color)
{
	char	*dst;

	dst = (char *)img->colors 
		+ (pos.y * img->line_length + pos.x * (img->bpp / 8));
	*(int*)dst = color;
}

	void
create_img(t_data *data, char *path, t_img *img)
{
	ft_putstr_fd("\nIMG00", 1);
	free_image(data, img, 0);
	img->ptr = 
		mlx_xpm_file_to_image(data->mlx, path, &img->size.x, &img->size.y);
	if (img->ptr == NULL)
		close_program(data, "Invalid or missing file at :\n   > ", path);
	img->colors = (int*)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	if (img->path != NULL)
		free(img->path);
	img->path = ft_strdup(path);
}
