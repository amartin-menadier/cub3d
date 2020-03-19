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

//il faudra penser a free les img des textures aussi
void	fill_texture(t_data *data, char *line, char *texture)
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
	if (!ft_strncmp(texture, "S ", 2))
		data->settings.Sprite_path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}
