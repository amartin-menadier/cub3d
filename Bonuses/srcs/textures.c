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
*get_sprite_image(t_piclib *lib, char text_number)
{
	if (text_number == '2')
		return (&lib->s2);
	else
		return (&lib->s3);
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
