/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:06:30 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 11:52:48 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** voir avec Celia pourquoi ca ne marche pas


char	**update_map(t_data *data, char **tmp, t_map *map, int i)
{
	i = 0;
	ft_putstr_fd("POSY\n", 1);
	free_map(map);
	ft_putstr_fd("POS1\n", 1);
	if (!(map->map = malloc(sizeof(char**) * (map->y))))
		error_exit(data, "Failed allocating memory for map\n", "");
	while (i < map->y)
	{
	ft_putstr_fd("POS2\n", 1);
		if (!(map->map[i] = malloc(sizeof(char*) * (map->x))))
			error_exit(data, "Failed allocating memory for map\n", "");
	ft_putstr_fd("POS4\n", 1);
		map->map[i] = ft_strcharcpy(map->map[i], *tmp[i], map->x, ' ');
	ft_putstr_fd("POS5\n", 1);
		free(*tmp[i]);
		*tmp[i] = NULL;
		i++;
	}
	ft_putstr_fd("POS9\n", 1);
	free(*tmp);
	*tmp = NULL;
return (map->map);
}
*/

char	**fill_tmp_map(t_data *data, t_map *map, char **tmp, char *line)
{
	int i;

	i = 0;
/*
// NB : Map_Height has not yet been incremented in fill_tmp
*/
	if (!(tmp = malloc(sizeof(char**) * (map->Height + 1))))
		error_exit(data, "Failed allocating memory for tmp map\n", "");
	while (i < map->Height + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char*) * (map->Width + 1))))
			error_exit(data, "Failed allocating memory for tmp map\n", "");
		if (i != (map->Height))
			tmp[i] = ft_strcharcpy(tmp[i], map->map[i], map->Width, ' ');
		else
			tmp[i] = ft_strcharcpy(tmp[i], line, map->Width, ' ');
		i++;
	}
	return (tmp);
}

void	fill_map(t_data *data, char *line, int i, t_map *map)
{
	char	**tmp;

	if (map->Width < (int)ft_strlen(line))
		map->Width = ft_strlen(line);
	i = 0;
	tmp = NULL;
	tmp = fill_tmp_map(data, map, tmp, line);
	free_map(map);
	map->Height = map->Height + 1;
	i = 0;
	if (!(map->map = malloc(sizeof(char**) * (map->Height))))
		error_exit(data, "Failed allocating memory for map\n", "");
	while (i < map->Height)
	{
		if (!(map->map[i] = malloc(sizeof(char*) * (map->Width))))
			error_exit(data, "Failed allocating memory for map\n", "");
		map->map[i] = ft_strcharcpy(map->map[i], tmp[i], map->Width, ' ');
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}

void	fill_resolution(t_data *data, char *line, t_settings *settings)
{
	int	i;
//rqjouter un messqge d'erreur si res deja set
	i = 1;
	settings->Resx = 0;
	settings->Resy = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		settings->Resx = (settings->Resx * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		settings->Resy = (settings->Resy * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	if (line[i])
		error_exit(data, "Wrong resolution in .cub file\n", "");
	if (settings->Resx < 50 || settings->Resy < 50)
		error_exit(data, "Resolution is too small\n", "");
	if (settings->Resx > 2560)
		settings->Resx = 2560;
	if (settings->Resy > 1440)
		settings->Resy = 1440;
}

/*
#include <mlx.h>

int     main(void)
{
	void    *mlx;
	void    *img;
	char    *relative_path = "./test.xpm";
	int     img_width;
	int     img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}
*/
/*
void	get_texture_img(t_data *data, char *path, t_img *textimg)
{
		textimg->tw = 0;
		textimg->th = 0;
	textimg->img = mlx_xpm_file_to_image(data->mlx, path, &textimg->tw, &textimg->th);
	textimg->addr = mlx_get_data_addr(textimg->img, &textimg->bits_per_pixel,
			&textimg->line_length, &textimg->endian);
}
*/

void	fill_texture(t_data *data, char *line, char *texture)
{
	char	*tmp;

	//renvoyer un message d'erreur si texture deja set

	if (!(tmp = ft_strtrim(&line[2], " ")))
		error_exit(data, "Failed allocating memory for path ", texture);
	if (ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".xpm", 4) &&
			ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".png", 4))
		error_exit(data, "Wrong file for texture ", texture);
	//ou check_texture_errors ? // erreur a changer en fonction extension voulue
	if (!ft_strncmp(texture, "NO", 2))
	{
//		data->settings.NO = ft_strdup(tmp);
	get_texture_img(data, tmp, &data->settings.NO);
	//	printf("\nI GET THERE\n");
	//	get_texture_img(data, tmp, &data->NO);

	}
	if (!ft_strncmp(texture, "SO", 2))
	get_texture_img(data, tmp, &data->settings.SO);
	//	data->settings.SO = ft_strdup(tmp);
	if (!ft_strncmp(texture, "WE", 2))
	get_texture_img(data, tmp, &data->settings.WE);
	//	data->settings.WE = ft_strdup(tmp);
	if (!ft_strncmp(texture, "EA", 2))
	get_texture_img(data, tmp, &data->settings.EA);
	//	data->settings.EA = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S ", 2))
		data->settings.S = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}

void	fill_color(t_data *data, char *line, char *color)
{
	char	*tmp;
	int		rgb;

	//rajouter un messqge d'erreur si color deja set

	if (!(tmp = ft_strtrim(&line[2], " ")))
		error_exit(data, "Failed allocating memory for color ", color);
	if ((rgb = get_rgb_from_string(tmp)) == -1)
	{
		free(tmp);
		tmp = NULL;
		error_exit(data, "Wrong color format - check ", color);
	}
	else if (!ft_strncmp(color, "F ", 2))
		data->settings.F = rgb;
	else if (!ft_strncmp(color, "C ", 2))
		data->settings.C = rgb;
	free(tmp);
	tmp = NULL;
}

void	fill_settings(t_data *data, char *line, int i)
{
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
		fill_map(data, line, i, &data->map);
}
