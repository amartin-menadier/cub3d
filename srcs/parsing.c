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

int		settings_all_set(t_data *data, t_settings *settings, char *line)
{
	if ((!ft_memcmp(line, "R ", 2) && settings->win_height) ||
		(!ft_memcmp(line, "NO ", 3) && settings->NO_path) ||
		(!ft_memcmp(line, "SO ", 3) && settings->SO_path) ||
		(!ft_memcmp(line, "EA ", 3) && settings->EA_path) ||
		(!ft_memcmp(line, "WE ", 3) && settings->WE_path) ||
		(!ft_memcmp(line, "S ", 2) && settings->Sprite_path) ||
		(!ft_memcmp(line, "F ", 2) && settings->Floor_color > -1) ||
		(!ft_memcmp(line, "C ", 2) && settings->Ceiling_color > -1))
			close_program(data, "One parameter is set twice\n", "");
	if (settings->win_width == -1 || settings->win_height == -1 ||
		settings->SO_path == NULL || settings->WE_path == NULL ||
		settings->EA_path == NULL || settings->NO_path == NULL ||
		settings->Sprite_path == NULL || settings->Floor_color == -1 ||
		settings->Ceiling_color == -1)
		return (0);
	else
		return (1);
}

int		check_settings(t_data *data, t_settings *settings, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && settings->map_height)
		close_program(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && !settings_all_set(data, settings, &line[i]))
		close_program(data, "Parameter missing before map\n", "");
	else if (line[i] != '1' && settings_all_set(data, settings, &line[i]))
		close_program(data, "Map not closed or invalid element\n", "");
	else if (line[i] != '1' && !settings_all_set(data, settings, &line[i]) &&
		!(!ft_memcmp(&line[i], "R ", 2) || !ft_memcmp(&line[i], "NO ", 3) ||
		!ft_memcmp(&line[i], "SO ", 3) || !ft_memcmp(&line[i], "WE ", 3) ||
		!ft_memcmp(&line[i], "EA ", 3) || !ft_memcmp(&line[i], "S ", 2) ||
		!ft_memcmp(&line[i], "F ", 2) || !ft_memcmp(&line[i], "C ", 2)))
			close_program(data, "Invalid parameter before map\n", "");
	return (i);
}

void	parse_line(t_data *data, char *line)
{
	int i;

	if ((i = check_settings(data, &data->settings, line)) == -1)
		return;
	if (line[i] == 'R' && line[i + 1] == ' ')
		fill_resolution(data, &line[i], &data->settings);
	if (line[i] == 'N' && line[i + 1] == 'O')
		fill_texture(data, &line[i], "NO");
	if (line[i] == 'S' && line[i + 1] == 'O')
		fill_texture(data, &line[i], "SO");
	if (line[i] == 'W' && line[i + 1] == 'E')
		fill_texture(data, &line[i], "WE");
	if (line[i] == 'E' && line[i + 1] == 'A')
		fill_texture(data, &line[i], "EA");
	if (line[i] == 'S' && line[i + 1] == ' ')
		fill_texture(data, &line[i], "S ");
	if (line[i] == 'F' && line[i + 1] == ' ')
		fill_color(data, &line[i], "F ");
	if (line[i] == 'C' && line[i + 1] == ' ')
		fill_color(data, &line[i], "C ");
	if (line[i] == '1')
		fill_map(data, line, i, &data->settings);
}

int		parse_cub(t_data *data)
{
	int		ret;
	char	*line;

	line = NULL;
	init_settings(&data->settings);
	while ((ret = get_next_line(data->settings.fd, &line)) > 0)
	{
		printf("GNL = %d - line is : >%s<\n", ret, line);//
		parse_line(data, line);
		free(line);
		line = NULL;
	}
//	parse_settings(data, line);
	printf("GNL = %d - line is : >%s<\n", ret, line);
	free(line);
	line = NULL;
	check_map_errors(data, &data->settings);
	//penser a close fd + message d'erreur ou pas
	return (data->settings.fd);
}
