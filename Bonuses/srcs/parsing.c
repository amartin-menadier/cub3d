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
settings_ok(t_data *data, t_settings *settings, char *line)
{
	if ((!ft_memcmp(line, "R ", 2) && settings->win_size.y)
		|| (!ft_memcmp(line, "NO ", 3) && settings->NO_path)
		|| (!ft_memcmp(line, "SO ", 3) && settings->SO_path)
		|| (!ft_memcmp(line, "EA ", 3) && settings->EA_path)
		|| (!ft_memcmp(line, "WE ", 3) && settings->WE_path)
		|| (!ft_memcmp(line, "S2 ", 3) && settings->S2_path)
		|| (!ft_memcmp(line, "S3 ", 3) && settings->S3_path)
		|| (!ft_memcmp(line, "F ", 2) && settings->flr_path)
		|| (!ft_memcmp(line, "C ", 2) && settings->clg_path))
			close_program(data, "One parameter is set twice\n", "");
	if (settings->win_size.x == -1 || settings->win_size.y == -1
		|| settings->SO_path == NULL || settings->WE_path == NULL
		|| settings->EA_path == NULL || settings->NO_path == NULL
		|| settings->S2_path == NULL || settings->S3_path == NULL
		|| settings->flr_path == NULL || settings->clg_path == NULL)
		return (0);
	else
		return (1);
}

	int
check_settings(t_data *data, t_settings *settings, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && settings->map_size.y)
		close_program(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && !settings_ok(data, settings, &line[i]))
		close_program(data, "Parameter missing before map\n", "");
	else if (line[i] != '1' && settings_ok(data, settings, &line[i]))
		close_program(data, "Map not closed or invalid element\n", "");
	else if (line[i] != '1' && !settings_ok(data, settings, &line[i])
		&& !(!ft_memcmp(&line[i], "R ", 2) || !ft_memcmp(&line[i], "NO ", 3)
		|| !ft_memcmp(&line[i], "SO ", 3) || !ft_memcmp(&line[i], "WE ", 3)
		|| !ft_memcmp(&line[i], "EA ", 3) || !ft_memcmp(&line[i], "S2 ", 3)
		|| !ft_memcmp(&line[i], "S3 ", 3)
		|| !ft_memcmp(&line[i], "F ", 2) || !ft_memcmp(&line[i], "C ", 2)))
			close_program(data, "Invalid parameter before map\n", "");
	return (i);
}

	void
parse_line(t_data *data, char *line)
{
	int i;

	if ((i = check_settings(data, &data->settings, line)) == -1)
		return;
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(data, &line[i], &data->settings);
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_texture_path(data, &line[i], "NO");
	if (line[i] == 'S' && line[i + 1] == 'O')
		get_texture_path(data, &line[i], "SO");
	if (line[i] == 'W' && line[i + 1] == 'E')
		get_texture_path(data, &line[i], "WE");
	if (line[i] == 'E' && line[i + 1] == 'A')
		get_texture_path(data, &line[i], "EA");
	if (line[i] == 'S' && line[i + 1] == '2')
		get_texture_path(data, &line[i], "S2");
	if (line[i] == 'S' && line[i + 1] == '3')
		get_texture_path(data, &line[i], "S3");
	if (line[i] == 'F' && line[i + 1] == ' ')
		get_texture_path(data, &line[i], "F");
	if (line[i] == 'C' && line[i + 1] == ' ')
		get_texture_path(data, &line[i], "C");
	if (line[i] == '1')
		get_map(data, line, i, &data->settings);
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

	line = NULL;
		ft_putstr_fd("\n41", 1);
		ft_putstr_fd("\n--", 1);
	init_settings(&data->settings);
		ft_putstr_fd("\n42", 1);
		ft_putstr_fd("\n--", 1);
	while ((ret = get_next_line(data->settings.fd, &line)) > 0)
	{
		parse_line(data, line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
		ft_putstr_fd("\n43", 1);
		ft_putstr_fd("\n--", 1);
	check_map_errors(data, &data->settings);
		ft_putstr_fd("\n44", 1);
		ft_putstr_fd("\n--", 1);
	get_sprites_data(data, &data->settings, data->settings.map);
		ft_putstr_fd("\n45", 1);
		ft_putstr_fd("\n--", 1);
	if ((close(data->settings.fd)) < 0)
		close_program(data, "Couldn't close .cub file", "");
		ft_putstr_fd("\n46", 1);
		ft_putstr_fd("\n--", 1);
	data->settings.done = 1;
}
