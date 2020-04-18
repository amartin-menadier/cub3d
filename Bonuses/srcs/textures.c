/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:06:30 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 11:52:48 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	t_img
*get_sprite_texture(t_frame *frame, char text_number)
{
	if (text_number == '2')
		return (&frame->S2_img);
	else
		return (&frame->S3_img);
}

	t_img
*get_wall_texture(t_frame *frame)
{
	t_img	*text_img;

	if (frame->side == 0)
	{
		if (frame->ray.x >0)
			text_img = &frame->EA_img;
		else
			text_img = &frame->WE_img;
	}
	else
	{
		if (frame->ray.y >0)
			text_img = &frame->SO_img;
		else
			text_img = &frame->NO_img;
	}
	frame->text.x = (int)(frame->wall_x * (double)text_img->size.x);
	if(frame->side == 0 && frame->ray.x > 0)
		frame->text.x = text_img->size.x - frame->text.x;
	if(frame->side == 1 && frame->ray.y < 0)
		frame->text.x = text_img->size.x - frame->text.x;
	return (text_img);
}

	void
get_texture_path(t_data *data, char *line, char *texture)
{
	char	*tmp;

	if (!(tmp = ft_strtrim(&line[2], " ")))
		close_program(data, "Failed allocating memory for path ", texture);
	if (ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".xpm", 4) &&
		ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".png", 4))
		close_program(data, "Wrong extension for file ", texture);
	if (!ft_strncmp(texture, "NO", 2))
		data->settings.NO_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "SO", 2))
		data->settings.SO_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "WE", 2))
		data->settings.WE_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "EA", 2))
		data->settings.EA_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S2", 2))
		data->settings.S2_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S3", 2))
		data->settings.S3_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "F", 1))
		data->settings.flr_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "C", 1))
		data->settings.clg_path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}
