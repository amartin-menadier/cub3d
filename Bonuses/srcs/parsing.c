/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:30:05 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 11:22:33 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	int
settings_ok(t_data *data, t_settings *settings, t_piclib *lib, char *line)
{
	if ((!ft_memcmp(line, "R ", 2) && settings->win_size.y)
		|| (!ft_memcmp(line, "EA ", 3) && lib->ea.path)
		|| (!ft_memcmp(line, "SO ", 3) && lib->so.path)
		|| (!ft_memcmp(line, "WE ", 3) && lib->we.path)
		|| (!ft_memcmp(line, "NO ", 3) && lib->no.path)
		|| (!ft_memcmp(line, "F ", 2) && lib->flr.path)
		|| (!ft_memcmp(line, "C ", 2) && lib->sky.path)
		|| (!ft_memcmp(line, "S2 ", 3) && lib->s2.path)
		|| (!ft_memcmp(line, "S3 ", 3) && lib->s3.path))
			close_program(data, "One parameter is set twice\n", "");
	if (settings->win_size.x == -1 || settings->win_size.y == -1
		|| lib->ea.path == NULL || lib->so.path == NULL
		|| lib->we.path == NULL || lib->no.path == NULL
		|| lib->flr.path == NULL || lib->sky.path == NULL
		|| lib->s2.path == NULL || lib->s3.path == NULL)
		return (0);
	else
		return (1);
}

	int
check_settings(t_data *data, t_settings *settings, t_piclib *lib, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && settings->map_size.y)
		close_program(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && !settings_ok(data, settings, lib,  &line[i]))
		close_program(data, "Parameter missing before map\n", "");
	else if (line[i] != '1' && settings_ok(data, settings, lib,  &line[i]))
		close_program(data, "Map not closed or invalid element\n", "");
	else if (line[i] != '1' && !settings_ok(data, settings, lib,  &line[i])
		&& !(!ft_memcmp(&line[i], "R ", 2)
		|| !ft_memcmp(&line[i], "SO ", 3) || !ft_memcmp(&line[i], "WE ", 3)
		|| !ft_memcmp(&line[i], "EA ", 3) || !ft_memcmp(&line[i], "NO ", 3)
		|| !ft_memcmp(&line[i], "F ", 2) || !ft_memcmp(&line[i], "C ", 2)
		|| !ft_memcmp(&line[i], "S2 ", 3) || !ft_memcmp(&line[i], "S3 ", 3)))
			close_program(data, "Invalid parameter before map\n", "");
	return (i);
}

	void
parse_line(t_data *data, t_settings *settings, t_piclib *lib, char *line)
{
	int i;

	if ((i = check_settings(data, settings, lib, line)) == -1)
		return;
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(data, &line[i], &data->settings);
	if (line[i] == 'S' && line[i + 1] == 'O')
		get_image_path(data, lib, &line[i], "SO");
	if (line[i] == 'W' && line[i + 1] == 'E')
		get_image_path(data, lib, &line[i], "WE");
	if (line[i] == 'E' && line[i + 1] == 'A')
		get_image_path(data, lib, &line[i], "EA");
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_image_path(data, lib, &line[i], "NO");
	if (line[i] == 'F' && line[i + 1] == ' ')
		get_image_path(data, lib, &line[i], "F");
	if (line[i] == 'C' && line[i + 1] == ' ')
		get_image_path(data, lib, &line[i], "C");
	if (line[i] == 'S' && line[i + 1] == '2')
		get_image_path(data, lib, &line[i], "S2");
	if (line[i] == 'S' && line[i + 1] == '3')
		get_image_path(data, lib, &line[i], "S3");
	if (line[i] == '1')
		get_map(data, line, i, settings);
}

	void
get_sprites_data(t_data *data, t_settings *settings, char **map)
{
	t_int	pos;
	int		i;

	pos.y = 1;
	i = 0;
	init_sprites(data, settings, &data->frame);
	while (pos.y < settings->map_size.y - 1 && i < settings->spr_count)
	{
		pos.x = 0;
		while (pos.x < settings->map_size.x && i < settings->spr_count)
		{
			if (map[pos.y][pos.x] >= '2' && map[pos.y][pos.x] <= '9')
				{
					settings->spr_x[i] = pos.x + 0.5;
					settings->spr_y[i] = pos.y + 0.5;
					settings->spr_text[i] = map[pos.y][pos.x];
					i++;
				}
			pos.x++;
		}
		pos.y++;
	}
	data->frame.spr_sorted = 0;
}

	void
parse_cub_file(t_data *data)
{
	int		ret;
	char	*line;
	// eventuellement enlever le fd de la structure

	line = NULL;
	init_settings(&data->settings);
	while ((ret = get_next_line(data->settings.fd, &line)) > 0)
	{
		parse_line(data, &data->settings, &data->piclib, line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	check_map_errors(data, &data->settings);
	get_sprites_data(data, &data->settings, data->settings.map);
	if ((close(data->settings.fd)) < 0)
		close_program(data, "Couldn't close .cub file", "");
	data->settings.done = 1;
}
