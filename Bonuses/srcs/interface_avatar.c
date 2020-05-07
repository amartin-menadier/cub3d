/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
get_minimap_avatar(t_data *data)
{
	t_img	*avatar;
	char *path;

	avatar = &data->piclib.avatar;
	if (data->life >= 80)
		path = ft_strdup("./textures/intellolcut.xpm");
	else if (data->life >= 33)
		path = ft_strdup("./textures/grinmacing.xpm");
	else
		path = ft_strdup("./textures/crying.xpm");
	create_img(data, path, avatar);
	free(path);
	path = NULL;
}

	int
get_avatar_color(t_data *data, t_img *avatar, t_dbl minimap_cam, int color)
{
	t_int	avat_pxl;
	t_dbl	dist_from_player;

	dist_from_player.x = minimap_cam.x - data->cam.x;
	dist_from_player.z = minimap_cam.z - data->cam.z;
	if (dist_from_player.x < -0.5 || dist_from_player.x >= 0.5
			|| dist_from_player.z < -0.5 || dist_from_player.z >= 0.5
			|| hypot(dist_from_player.x, dist_from_player.z) > 0.5)
		return (color);
	avat_pxl.x = (int)((dist_from_player.x + 0.5) * avatar->size.x);
	avat_pxl.y = (int)((dist_from_player.z + 0.5) * avatar->size.y);
	color = img_color(avatar->colors, avat_pxl.x, avat_pxl.y, avatar->size);
	return (color);
}
