/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:17:55 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:17 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_window(t_data *data, int mod)
{
	(void)mod;//potentiellement a degager
	init_data(data);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	ft_putstr_fd("\nEND_OF_PROGRAM\n", 1);//a supprimer
//	system("leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

int		error_exit(t_data *data, char *error_msg, char *str)
{
	if (ft_memcmp(str, "\\o/\n", 4))
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_msg, 1);
	ft_putstr_fd(str, 1);
//	print_params(data);
	free_settings(&data->settings);
//	data->map.Height += 1;
	free_map(&data->map);
//	init_data(data);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	ft_putstr_fd("\nEND_OF_PROGRAM\n", 1);//a supprimer
//	system("leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

int		settings_is_set(t_settings *settings)
{
	if (settings->Resx == -1 || settings->Resy == -1 || settings->NO == NULL ||
			settings->SO == NULL || settings->WE == NULL || settings->EA == NULL ||
			settings->S == NULL || settings->F == -1 || settings->C == -1)
		return (0);
	else
		return (1);
}

int		is_map(t_data *data, t_map *map, int i, int j)
{
	char c;

	c = map->map[i][j];
	if (c == ' ')
		return (1);
	if (c == '1')
		return (2);
	if (c == '2' || c == '0')
		return (3);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map->player_orientation == 0)
		{
			map->player_orientation = c;
			map->pos_x = j;
			map->pos_y = i;
		}
		else if (i != map->pos_y || j != map->pos_x)
			error_exit(data, "More than one player set", "");
		return (4);
	}
	return (0);
}

void	check_map_neighbors(t_data *data, t_map *map, int i, int j)
{
	int x;
	int y;

	x = j - 1;
	while (x <= j + 1)
	{
		y = i - 1;
		while (y <= i + 1)
		{
			if (map->map[y][x] == '\0' || map->map[y][x] == ' ')
				error_exit(data, "Map not closed", "");
			if (!is_map(data, map, y, x))
				error_exit(data, "Wrong object in map", "");
			y++;
		}
		x++;
	}
}

void	check_map_errors(t_data *data, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->Height)
	{
		j = 0;
		while (j < (int)ft_strlen(map->map[i]))
		{
			if ((i == 0 || i == (map->Height - 1)) && is_map(data, map, i, j) > 2)
				error_exit(data, "Map not closed at top or bottom", "");
			if (!is_map(data, map, i, j))
				error_exit(data, "Wrong object in map", "");
			if (is_map(data, map, i, j) >= 3)
				check_map_neighbors(data, map, i, j);
			j++;
		}
		i++;
	}
	if (map->player_orientation == 0)
		error_exit(data, "No map or no player set :'(", "");
}

void	check_settings_errors(t_data *data, char *line)
{
	if (line[0] == '1' && !settings_is_set(&data->settings))
		error_exit(data, "Element missing or map is not last\n", "");
	else if (line[0] != '1' && settings_is_set(&data->settings))
		error_exit(data, "Map not closed or something is out\n", "");
	else if (line[0] != '1' && !settings_is_set(&data->settings))
	{
		if (!ft_memcmp(line, "R ", 2) || !ft_memcmp(line, "NO ", 3) ||
				!ft_memcmp(line, "SO ", 3) || !ft_memcmp(line, "WE ", 3) ||
				!ft_memcmp(line, "EA ", 3) || !ft_memcmp(line, "S ", 2) ||
				!ft_memcmp(line, "F ", 2) || !ft_memcmp(line, "C ", 2))
			return ;
		else
			error_exit(data, "Wrong element name(s) before map\n", "");
	}
	return ;
}

void	check_args_errors(t_data *data, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		error_exit(data, "Invalid number of arguments\n", "");
	if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		error_exit(data, "Second argument is not --save\n", "");
	if (ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		error_exit(data, "File extension is not .cub\n", "");
	if ((data->settings.fd = open(argv[1], O_RDONLY)) == -1)
		error_exit(data, "Couldn't open .cub file\n", "");
}
