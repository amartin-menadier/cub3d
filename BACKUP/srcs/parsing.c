/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:30:05 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/09 14:04:03 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(t_data *data, t_map *map)
{
	check_map_errors(data, map);
}

void	parse_scene(t_data *data, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && data->map.y)
		error_exit(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return ;
//	printf("line is : >%s<\n", &line[i]);
	check_scene_errors(data, &line[i]);
	fill_settings(data, line, i);
}

int		parse_cub(t_data *data)
{
	int		ret;
	char	*line;

	line = NULL;
	init_scene(&data->scene);
	init_map(&data->map);
	while ((ret = get_next_line(data->scene.fd, &line)) > 0)
	{
		printf("GNL = %d - line is : >%s<\n", ret, line);//
		parse_scene(data, line);
		free(line);
		line = NULL;
	}
//	parse_scene(data, line);
	printf("GNL = %d - line is : >%s<\n", ret, line);
	free(line);
	line = NULL;
	parse_map(data, &data->map);
	//penser a close fd + message d'erreur ou pas
	return (data->scene.fd);
}
