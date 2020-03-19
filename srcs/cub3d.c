/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//angle du champ visuel : 60 degres
//fov = field of view = champ de vision
//tan ^ABC^ (rectangle en A) = AC/AB => AB =AC/tan ^ABC^ // tan a = Ya/Xa
//Digital differential analyser = verification des mus verticaux et horizontaux separement
//Il faut creer une image. Les pixels iront dans cette image et on affichera l'image. Sinon les pixels essaient de s'afficher en meme temps que la fenetre et tout bugue
//Il faut creer une image temporaire pour stocker la mouvelle image sinon le rendu fera de la merde. Traduction approximative. 

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->colors + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	get_texture_img(t_data *data, char *path, t_img *textimg)
{
	textimg->img = mlx_xpm_file_to_image(data->mlx, path, &textimg->tw, &textimg->th);
	textimg->colors = (int*)mlx_get_data_addr(textimg->img, &textimg->bits_per_pixel,
			&textimg->line_length, &textimg->endian);
}

int		render_texture(t_data *data)
{
	int	x;
	int	y;

		int tw = data->settings.NO.tw;
		int th = data->settings.NO.th;
	x = 0;
	while (x < tw)
	{
		y = 0;
		while (y < th)
		{
			int color = data->settings.NO.colors[y + x];
			my_mlx_pixel_put(&data->img, x, y, color);
		//	printf("%d", data->NO.colors[y+x]);
			y++;
		}
			printf("\n");
		x++;
	}
mlx_put_image_to_window(data->mlx, data->win, data->settings.NO.img, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	//histoire du --save en bmp a faire
	data.mlx = mlx_init();
	parse_cub(&data);
	init_data(&data);//peut-etre remplacer par init window et ini image;
//	ft_putstr_fd("INIT DATA OVER\n", 1);

	//    data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
	//			&data.img.line_length, &data.img.endian);
//	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
//	ft_putstr_fd("MLX IMG TO WIN OVER\n", 1);
	hook_event(&data);
//	ft_putstr_fd("HOOK EVENT OVER\n", 1);
	//	mlx_hook(data.win, 2, 1L << 0, presskey, &data);
	//	mlx_hook(data.win, 17, 1L << 17, red_cross, &data);
/*
mlx_loop_hook(data.mlx, render_texture, &data);
*/
mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);//permet a la fenetre de rester ouverte
	//penser a enlever le fsanitize du makefile
	return (0);
}
