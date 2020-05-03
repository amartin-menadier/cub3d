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
	if (data->set.life >= 80)
		path = ft_strdup("./textures/intellolcut.xpm");
	else if (data->set.life >= 33)
		path = ft_strdup("./textures/grinmacing.xpm");
	else
		path = ft_strdup("./textures/crying.xpm");
	create_img(data, path, avatar);
	free(path);
	path = NULL;
}

	int
get_avatar_color(t_data *data, t_img avatar, t_dbl minimap_pos, int color)
{
	t_int	avat_pxl;
	t_dbl	dist_from_player;

	dist_from_player.x = minimap_pos.x - data->set.pos.x;
	dist_from_player.y = minimap_pos.y - data->set.pos.y;
	if (dist_from_player.x < -0.5 || dist_from_player.x >= 0.5
			|| dist_from_player.y < -0.5 || dist_from_player.y >= 0.5
			|| hypot(dist_from_player.x, dist_from_player.y) > 0.5)
		return (color);
	avat_pxl.x = (int)((dist_from_player.x + 0.5) * avatar.size.x);
	avat_pxl.y = (int)((dist_from_player.y + 0.5) * avatar.size.y);
	color = avatar.colors[(avatar.size.x * avat_pxl.y + avat_pxl.x)];
	return (color);
}
