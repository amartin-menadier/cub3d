/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:44:13 by amenadier         #+#    #+#             */
/*   Updated: 2020/07/20 17:41:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned char
	*create_bmp_info_header(t_img *scr)
{
	static unsigned char	info_header[40];
	int						i;

	i = 0;
	while (i < 40)
		info_header[i++] = 0;
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(scr->size.x);
	info_header[5] = (unsigned char)(scr->size.x >> 8);
	info_header[6] = (unsigned char)(scr->size.x >> 16);
	info_header[7] = (unsigned char)(scr->size.x >> 24);
	info_header[8] = (unsigned char)(-scr->size.y);
	info_header[9] = (unsigned char)(-scr->size.y >> 8);
	info_header[10] = (unsigned char)(-scr->size.y >> 16);
	info_header[11] = (unsigned char)(-scr->size.y >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(scr->bpp);
	return (info_header);
}

unsigned char
	*create_bmp_file_header(t_img *scr, int padding_size)
{
	int						file_size;
	static unsigned char	file_header[14];
	int						i;

	i = 0;
	while (i < 14)
		file_header[i++] = 0;
	file_size = 14 + 40
		+ ((scr->bpp / 8) * scr->size.x + padding_size) * scr->size.y;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

void
	fill_bmp(t_data *data, unsigned char *copy, t_img *scr, int bmp_fd)
{
	unsigned char	padding[3];
	unsigned char	*file_header;
	unsigned char	*info_header;
	int				i;

	padding[0] = 0;
	padding[1] = 0;
	padding[2] = 0;
	i = (4 - (scr->size.x * scr->bpp / 8) % 4) % 4;
	file_header = create_bmp_file_header(scr, i);
	info_header = create_bmp_info_header(scr);
	write(bmp_fd, file_header, 14);
	write(bmp_fd, info_header, 40);
	i = 0;
	while (i < scr->size.y)
	{
		write(bmp_fd, copy + (i * 4 * scr->size.x), 4 * scr->size.x);
		write(bmp_fd, padding, (4 - (scr->size.x * scr->bpp / 8) % 4) % 4);
		i++;
	}
	if (close(bmp_fd) < 0)
		close_program(data, "Couldn't close bmp fd", "");
}

char
	*get_screenshot_path(t_data *data, char *path)
{
	char *path_number;
	char *file_name;

	if (data->save == 0)
		data->save++;
	data->save++;
	if (!ft_strncmp(path, "start.bmp", 9))
		return (ft_strcat(path, ""));
	path_number = ft_itoa(data->save - 2);
	file_name = ft_strcat(path_number, ".bmp");
	free(path_number);
	path_number = NULL;
	path = ft_strcat(path, file_name);
	free(file_name);
	file_name = NULL;
	return (path);
}

void
	create_bmp(t_data *data, t_img *scr, char *path)
{
	unsigned char	copy[scr->size.y][scr->size.x][scr->bpp / 8];
	t_int			pos;
	int				color;
	int				bmp_fd;

	path = get_screenshot_path(data, path);
	pos.x = 0;
	while (pos.x < scr->size.y)
	{
		pos.y = 0;
		while (pos.y < scr->size.x)
		{
			color = scr->colors[(pos.x * scr->size.x + pos.y)];
			int_to_rgb(copy[pos.x][pos.y], color);
			pos.y++;
		}
		pos.x++;
	}
	if ((bmp_fd = open(path, O_RDWR | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		close_program(data, "Couldn't create screenshot at ", path);
	fill_bmp(data, (unsigned char *)copy, scr, bmp_fd);
	free(path);
	path = NULL;
}
