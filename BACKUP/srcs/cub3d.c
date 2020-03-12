/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/09 14:33:39 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//angle du champ visuel : 60 degres
//fov = field of view = champ de vision
//tan ^ABC^ (rectangle en A) = AC/AB => AB =AC/tan ^ABC^ // tan a = Ya/Xa
//Digital differential analyser = verification des mus verticaux et horizontaux separement
//Il faut creer une image. Les pixels iront dans cette image et on affichera l'image. Sinon les pixels essaient de s'afficher en meme temps que la fenetre et tout bugue
//Il faut creer une image temporaire pour stocker la mouvelle image sinon le rendu fera de la merde. Traduction approximative. 

#include "cub3d.h"

void	print_params(t_data *data)//outil de verification a supprimer
{
	int i = 0;
	int j = 0;

	printf("\nWin_Rx = %d", data->scene.win_Rx);
	printf("\nWin_Ry = %d", data->scene.win_Ry);
	printf("\nNO_text_path = %s", data->scene.NO);
	printf("\nSO_text_path = %s", data->scene.SO);
	printf("\nWE_text_path = %s", data->scene.WE);
	printf("\nEA_text_path = %s", data->scene.EA);
	printf("\nSprite_text_path = %s", data->scene.S);
	printf("\nFloor color = %d", data->scene.F);
	printf("\nCeiling color = %d", data->scene.C);
	printf("\nMap_width = %d", data->map.x);
	printf("\nMap_height = %d", data->map.y);
	printf("\nPlayer orientation = >%c<", data->map.player_orientation);
	printf("\nPlayer is located at (%d,%d)", data->map.pos_x, data->map.pos_y);
	while (i < data->map.y)
	{
		j = 0;
		if (i <= 9)
			printf("\nmap [ %d] : >", i);
		else
			printf("\nmap [%d] : >", i);
		while (j < (int)ft_strlen(data->map.map[i]))
		{
			printf("%c ", data->map.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	printf("\n\n");
}

int		close_window(t_data *data, int mod)
{
	(void)mod;//potentiellement a degager
	init_data(data);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	ft_putstr_fd("\nEND_OF_PROGRAM\n", 1);//a supprimer
	system("leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		render_next_frame(t_data *data)
{
	int	x;
	int	y;

	update_image(data);
	y = 0;
	while (y < data->scene.win_Ry)
	{
		x = 0;
		while (x < data->scene.win_Rx)
		{
			my_mlx_pixel_put(&data->img, x, y, (y * x * (data->keycode)));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	//histoire du --save en bmp a faire
	parse_cub(&data);
	init_data(&data);//peut-etre remplacer par init window et ini image;
//    int     img_width;
//    int     img_height;

//  data.img.img = mlx_xpm_file_to_image(data.mlx, "./texture/test.xpm", &img_width, &img_height);
//    data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
//			&data.img.line_length, &data.img.endian);
//	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	hook_event(&data);
	mlx_loop(data.mlx);//permet a la fenetre de rester ouverte
	//penser a enlever le fsanitize du makefile
	return (0);
}
