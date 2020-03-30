#include "cub3d.h"

	unsigned char*
create_bmp_info_header(t_img *img)
{
	static unsigned char	info_header[40];
	int						i;

	i = 0;
	while (i < 40)
		info_header[i++] = 0;
	info_header[ 0] = (unsigned char)(40);
	info_header[ 4] = (unsigned char)(img->tw    );
	info_header[ 5] = (unsigned char)(img->tw>> 8);
	info_header[ 6] = (unsigned char)(img->tw>>16);
	info_header[ 7] = (unsigned char)(img->tw>>24);
	info_header[ 8] = (unsigned char)(-img->th    );
	info_header[ 9] = (unsigned char)(-img->th>> 8);
	info_header[10] = (unsigned char)(-img->th>>16);
	info_header[11] = (unsigned char)(-img->th>>24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(img->bpp);
	return (info_header);
}

	unsigned char*
create_bmp_file_header(t_img *img, int padding_size)
{
	int						file_size;
	static unsigned char	file_header[14];
	int						i;

	i = 0;
	while (i < 14)
		file_header[i++] = 0;
	file_size = 14 + 40 + ((img->bpp / 8) * img->tw + padding_size) * img->th;
	file_header[ 0] = (unsigned char)('B');
	file_header[ 1] = (unsigned char)('M');
	file_header[ 2] = (unsigned char)(file_size    );
	file_header[ 3] = (unsigned char)(file_size>> 8);
	file_header[ 4] = (unsigned char)(file_size>>16);
	file_header[ 5] = (unsigned char)(file_size>>24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

	void
fill_bmp(t_data *data, unsigned char *image, t_img *img, int bmp_fd)
{
	unsigned char padding[3] = {0, 0, 0};
	unsigned char* file_header;
	unsigned char* info_header;
	int i;

	i = (4 - (img->tw * img->bpp / 8) % 4) % 4;
	file_header = create_bmp_file_header(img, i);
	info_header = create_bmp_info_header(img);
	write(bmp_fd, file_header, 14);
	write(bmp_fd, info_header, 40);
	i = 0;
	while (i < img->th)
	{
		write(bmp_fd, image+(i * 4 * img->tw), 4 *img->tw);
		write(bmp_fd, padding, (4 - (img->tw * img->bpp / 8) % 4) % 4);
		i++;
	}
	if (close(bmp_fd) < 0)
		close_program(data, "Couldn't close bmp fd", "");
}

	char 
*get_screenshot_path(t_data *data, char *path)
{
	char *pathnumber;
	char *filename;

	if (data->save == 0)
		data->save++;
	data->save++;
	if (!ft_strncmp(path, "start.bmp", 9))
		return (ft_strcat(path, ""));
	pathnumber = ft_itoa(data->save - 2);
	filename = ft_strcat(pathnumber, ".bmp");
	free(pathnumber);
	pathnumber = NULL;
	path = ft_strcat(path, filename);
	free(filename);
	filename = NULL;
	return (path);
}

	void 
create_bmp(t_data *data, t_img *img, char *path)
{
	unsigned char	image[img->th][img->tw][img->bpp / 8];
	t_vector		pos;
	int				color;
	int				bmp_fd;

	path = get_screenshot_path(data, path);
	pos.x = 0;
	while (pos.x < img->th)
	{
		pos.y = 0;
		while (pos.y < img->tw)
		{
			color  = img->colors[pos.x * img->tw + pos.y];
			int_to_rgb(image[pos.x][pos.y], color);
			pos.y++;
		}
		pos.x++;
	}
	if ((bmp_fd = open(path, O_RDWR | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		close_program(data, "Couldn't create screenshot at ", path);
	fill_bmp(data, (unsigned char *)image, img, bmp_fd);
	free(path);
	path = NULL;
}