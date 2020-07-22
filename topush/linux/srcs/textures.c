/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:31:09 by amenadier         #+#    #+#             */
/*   Updated: 2020/07/21 15:42:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img
	*get_texture_img(t_frame *frame)
{
	t_img	*text_img;

	if (frame->side == 0)
	{
		if (frame->ray.x > 0)
			text_img = &frame->ea_img;
		else
			text_img = &frame->we_img;
	}
	else
	{
		if (frame->ray.y > 0)
			text_img = &frame->so_img;
		else
			text_img = &frame->no_img;
	}
	frame->text.x = (int)(frame->wall_x * (double)text_img->size.x);
	if (frame->side == 0 && frame->ray.x > 0)
		frame->text.x = text_img->size.x - frame->text.x - 1;
	if (frame->side == 1 && frame->ray.y < 0)
		frame->text.x = text_img->size.x - frame->text.x - 1;
	return (text_img);
}

void
	test_path(t_data *data, char *texture)
{
	int fd;

	if (!ft_strncmp(texture, "NO", 2))
		if ((fd = open(data->settings.no_path, O_RDONLY)) == -1)
			close_program(data, "Wrong path for ", texture);
	if (!ft_strncmp(texture, "SO", 2))
		if ((fd = open(data->settings.so_path, O_RDONLY)) == -1)
			close_program(data, "Wrong path for ", texture);
	if (!ft_strncmp(texture, "WE", 2))
		if ((fd = open(data->settings.we_path, O_RDONLY)) == -1)
			close_program(data, "Wrong path for ", texture);
	if (!ft_strncmp(texture, "EA", 2))
		if ((fd = open(data->settings.ea_path, O_RDONLY)) == -1)
			close_program(data, "Wrong path for ", texture);
	if (!ft_strncmp(texture, "S ", 2))
		if ((fd = open(data->settings.s_path, O_RDONLY)) == -1)
			close_program(data, "Wrong path for ", texture);
}

void
	get_texture(t_data *data, char *line, char *texture)
{
	char	*tmp;

	if (!(tmp = ft_strtrim(&line[2], " ")))
		close_program(data, "Failed allocating memory for path ", texture);
	if (ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".xpm", 4) &&
		ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".png", 4))
		close_program(data, "Wrong extension for file ", texture);
	if (!ft_strncmp(texture, "NO", 2))
		data->settings.no_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "SO", 2))
		data->settings.so_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "WE", 2))
		data->settings.we_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "EA", 2))
		data->settings.ea_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S ", 2))
		data->settings.s_path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	test_path(data, texture);
}
