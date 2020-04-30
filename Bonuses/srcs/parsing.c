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
set_ok(t_data *data, t_set *set, t_piclib *lib, char *line)
{
	if ((!ft_memcmp(line, "R ", 2) && set->win_size.y)
		|| (!ft_memcmp(line, "EA ", 3) && lib->ea.path)
		|| (!ft_memcmp(line, "SO ", 3) && lib->so.path)
		|| (!ft_memcmp(line, "WE ", 3) && lib->we.path)
		|| (!ft_memcmp(line, "NO ", 3) && lib->no.path)
		|| (!ft_memcmp(line, "F ", 2) && lib->flr.path)
		|| (!ft_memcmp(line, "C ", 2) && lib->sky.path)
		|| (!ft_memcmp(line, "S2 ", 3) && lib->s2.path)
		|| (!ft_memcmp(line, "S3 ", 3) && lib->s3.path))
			close_program(data, "One parameter is set twice\n", "");
	if (set->win_size.x == -1 || set->win_size.y == -1
		|| lib->ea.path == NULL || lib->so.path == NULL
		|| lib->we.path == NULL || lib->no.path == NULL
		|| lib->flr.path == NULL || lib->sky.path == NULL
		|| lib->s2.path == NULL || lib->s3.path == NULL)
		return (0);
	else
		return (1);
}

	int
check_set(t_data *data, t_set *set, t_piclib *lib, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && set->map_size.y)
		close_program(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && !set_ok(data, set, lib,  &line[i]))
		close_program(data, "Parameter missing before map\n", "");
	else if (line[i] != '1' && set_ok(data, set, lib,  &line[i]))
		close_program(data, "Map not closed or invalid element\n", "");
	else if (line[i] != '1' && !set_ok(data, set, lib,  &line[i])
		&& !(!ft_memcmp(&line[i], "R ", 2)
		|| !ft_memcmp(&line[i], "SO ", 3) || !ft_memcmp(&line[i], "WE ", 3)
		|| !ft_memcmp(&line[i], "EA ", 3) || !ft_memcmp(&line[i], "NO ", 3)
		|| !ft_memcmp(&line[i], "F ", 2) || !ft_memcmp(&line[i], "C ", 2)
		|| !ft_memcmp(&line[i], "S2 ", 3) || !ft_memcmp(&line[i], "S3 ", 3)))
			close_program(data, "Invalid parameter before map\n", "");
	return (i);
}

	void
parse_line(t_data *data, t_set *set, t_piclib *lib, char *line)
{
	int i;

	if ((i = check_set(data, set, lib, line)) == -1)
		return;
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(data, &line[i], &data->set);
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
		get_map(data, line, i, set);
}

	void
get_sprites_data(t_data *data, t_set *set, char **map)
{
	t_int	pos;
	int		i;

	if (set->spr != NULL)
		free(set->spr);
	set->spr = NULL;
	if (!(set->spr = malloc(sizeof(double *) * 2 * set->spr_count)))
		close_program(data, "Couldn't allocate mem for spr", "");
	pos.y = 1;
	i = 0;
	while (pos.y < set->map_size.y - 1 && i < set->spr_count)
	{
		pos.x = 0;
		while (pos.x < set->map_size.x && i < set->spr_count)
		{
			if (map[pos.y][pos.x] >= '2' && map[pos.y][pos.x] <= '9')
				{
					set->spr[i].x = pos.x + 0.5;
					set->spr[i].y = pos.y + 0.5;
					i++;
				}
			pos.x++;
		}
		pos.y++;
	}
}

	void
parse_cub_file(t_data *data)
{
	int		ret;
	char	*line;
	int		fd;
	// eventuellement enlever le fd de la structure

	line = NULL;
	if ((fd = open(data->cub_path, O_RDONLY)) == -1)
		close_program(data, "Couldn't open .cub file\n", "");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_line(data, &data->set, &data->piclib, line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	check_map_errors(data, &data->set);
	get_sprites_data(data, &data->set, data->set.map);
	printf("\n----");
	printf("\nPARS8 spr[%d] = (%f;%f)", 2, data->set.spr[2].x, data->set.spr[2].y);
	printf("\n----");
	if ((close(fd)) < 0)
		close_program(data, "Couldn't close .cub file", "");
//	data->set.done = 1;
}
