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

	t_img
*get_sprite_image(char **map, t_dbl spr, t_piclib *piclib)
{
	char	value;

	value = map[(int)spr.z][(int)spr.x];
	if (value == '2')
		return (&piclib->s2);
	else
		return (&piclib->s3);
}

	void
get_image_path(t_data *data, t_piclib *piclib, char *line, char *texture)
{
	char	*tmp;

	if (!(tmp = ft_strtrim(&line[2], " ")))
		close_program(data, "Failed allocating memory for path ", texture);
	if (ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".xpm", 4) &&
		ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".png", 4))
		close_program(data, "Wrong extension for file ", texture);
	if (!ft_strncmp(texture, "SO", 2))
		piclib->so.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "WE", 2))
		piclib->we.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "EA", 2))
		piclib->ea.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "NO", 2))
		piclib->no.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "F", 1))
		piclib->flr.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "C", 1))
		piclib->sky.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S2", 2))
		piclib->s2.path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S3", 2))
		piclib->s3.path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
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
create_img(t_data *data, char *path, t_img *img)
{
	char *tmp;

	tmp = ft_strdup(path);
	free_image(data, img);
	img->ptr = 
		mlx_xpm_file_to_image(data->mlx, tmp, &img->size.x, &img->size.y);
	if (img->ptr == NULL)
		close_program(data, "create_img/Invalid or missing file at : ", tmp);
	img->colors = (int*)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	img->path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}
