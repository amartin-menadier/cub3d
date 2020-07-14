/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_images_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:45:14 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_img
	*get_sprite_image(char **map, t_dbl spr, t_piclib *piclib)
{
	char	value;

	value = map[(int)spr.z][(int)spr.x];
	if (value == '2')
		return (&piclib->s2);
	if (value == '3')
		return (&piclib->s3);
	if (value == '4')
		return (&piclib->s4);
	if (value == '5')
		return (&piclib->s5);
	else
		return (&piclib->s4);
}

void
	get_sprite_path(t_piclib *piclib, char *tmp, char sprite_number)
{
	if (sprite_number == '2')
		piclib->s2.path = ft_strdup(tmp);
	if (sprite_number == '3')
		piclib->s3.path = ft_strdup(tmp);
	if (sprite_number == '4')
		piclib->s4.path = ft_strdup(tmp);
	if (sprite_number == '5')
		piclib->s5.path = ft_strdup(tmp);
	if (sprite_number == '6')
		piclib->s6.path = ft_strdup(tmp);
	if (sprite_number == '7')
		piclib->s7.path = ft_strdup(tmp);
	if (sprite_number == '8')
		piclib->s8.path = ft_strdup(tmp);
	if (sprite_number == '9')
		piclib->s9.path = ft_strdup(tmp);
}

void
	get_image_path(t_data *data, t_piclib *piclib, char *line, char *texture)
{
	char	*tmp;
	int		fd;

	tmp = ft_strtrim(&line[2], " ");
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
	if (line[0] == 'S' && ft_isdigit(texture[0]))
		get_sprite_path(piclib, tmp, texture[0]);
	if ((fd = open(tmp, O_RDONLY)) == -1)
		close_program(data, "Counld open file for path: ", tmp);
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
		close_program(data, "Invalid or missing file at : ", tmp);
	img->colors = (int*)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	img->path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}
