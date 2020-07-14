/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parsing_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:30:05 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 18:59:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	one_parameter_already_set(t_data *data, t_piclib *lib, char *line)
{
	if ((!ft_memcmp(line, "R ", 2) && data->win.size.y)
		|| (!ft_memcmp(line, "EA ", 3) && lib->ea.path)
		|| (!ft_memcmp(line, "SO ", 3) && lib->so.path)
		|| (!ft_memcmp(line, "WE ", 3) && lib->we.path)
		|| (!ft_memcmp(line, "NO ", 3) && lib->no.path)
		|| (!ft_memcmp(line, "F ", 2) && lib->flr.path)
		|| (!ft_memcmp(line, "C ", 2) && lib->sky.path)
		|| (!ft_memcmp(line, "S2 ", 3) && lib->s2.path)
		|| (!ft_memcmp(line, "S3 ", 3) && lib->s3.path)
		|| (!ft_memcmp(line, "S4 ", 3) && lib->s4.path)
		|| (!ft_memcmp(line, "S5 ", 3) && lib->s5.path)
		|| (!ft_memcmp(line, "S6 ", 3) && lib->s6.path)
		|| (!ft_memcmp(line, "S7 ", 3) && lib->s7.path)
		|| (!ft_memcmp(line, "S8 ", 3) && lib->s8.path)
		|| (!ft_memcmp(line, "S9 ", 3) && lib->s9.path))
		return (1);
	else
		return (0);
}

int
	data_ok(t_data *data, t_piclib *lib, char *line)
{
	if (one_parameter_already_set(data, lib, line))
		close_program(data, "One parameter is set twice\n", "");
	if (data->win.size.x == -1 || data->win.size.y == -1
		|| lib->ea.path == NULL || lib->so.path == NULL
		|| lib->we.path == NULL || lib->no.path == NULL
		|| lib->flr.path == NULL || lib->sky.path == NULL
		|| lib->s2.path == NULL || lib->s3.path == NULL)
		return (0);
	else
		return (1);
}

int
	check_data(t_data *data, t_piclib *lib, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && data->map_size.z)
		close_program(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && !data_ok(data, lib, &line[i]))
		close_program(data, "Parameter missing before map\n", "");
	else if (line[i] != '1' && data_ok(data, lib, &line[i]))
		close_program(data, "Map not closed or invalid element\n", "");
	else if (line[i] != '1' && !data_ok(data, lib, &line[i])
		&& !(!ft_memcmp(&line[i], "R ", 2)
		|| !ft_memcmp(&line[i], "SO ", 3) || !ft_memcmp(&line[i], "WE ", 3)
		|| !ft_memcmp(&line[i], "EA ", 3) || !ft_memcmp(&line[i], "NO ", 3)
		|| !ft_memcmp(&line[i], "F ", 2) || !ft_memcmp(&line[i], "C ", 2)
		|| !ft_memcmp(&line[i], "S2 ", 3) || !ft_memcmp(&line[i], "S3 ", 3)
		|| !ft_memcmp(&line[i], "S4 ", 3) || !ft_memcmp(&line[i], "S5 ", 3)
		|| !ft_memcmp(&line[i], "S6 ", 3) || !ft_memcmp(&line[i], "S7 ", 3)
		|| !ft_memcmp(&line[i], "S8 ", 3) || !ft_memcmp(&line[i], "S9 ", 3)))
		close_program(data, "Invalid parameter before map\n", line);
	return (i);
}

void
	parse_line(t_data *data, t_piclib *lib, char *line)
{
	int i;

	if ((i = check_data(data, lib, line)) == -1)
		return ;
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(data, &line[i]);
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
	if (line[i] == 'S' && ft_isdigit(line[i + 1]))
		get_image_path(data, lib, &line[i], &line[i + 1]);
	if (line[i] == '1')
		get_map(data, line, i);
}

void
	parse_cub_file(t_data *data)
{
	int		ret;
	char	*line;
	int		fd;

	line = NULL;
	if ((fd = open(data->cub_path, O_RDONLY)) == -1)
		close_program(data, "Couldn't open .cub file\n", "");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_line(data, &data->piclib, line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	check_map_errors(data);
	get_sprites_in_map(data, data->map);
	if ((close(fd)) < 0)
		close_program(data, "Couldn't close .cub file", "");
}
