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

void	print_params2(t_data *data)//outil de verification a supprimer
{
	int i = 0;
	int j = 0;

	printf("\nWin_Rx = %d", data->settings.Resx);
	printf("\nWin_Ry = %d", data->settings.Resy);
	printf("\nNO_text_path = %s", data->settings.NO);
	printf("\nSO_text_path = %s", data->settings.SO);
	printf("\nWE_text_path = %s", data->settings.WE);
	printf("\nEA_text_path = %s", data->settings.EA);
	printf("\nSprite_text_path = %s", data->settings.S);
	printf("\nFloor color = %x", data->settings.F);
	printf("\nCeiling color = %x", data->settings.C);
	printf("\nMap_width = %d", data->map.Width);
	printf("\nMap_height = %d", data->map.Height);
	printf("\nPlayer is located at (%f,%f)", data->map.pos_x, data->map.pos_y);
	printf("\nPlayer orientation = >%c<", data->map.player_orientation);
	printf("\n\nRAYCASTING\ninitdirX = %f", data->ray.dirX);
	printf("\ninitdirY = %f", data->ray.dirY);
	printf("\nrayX = %f", data->ray.rayX);
	printf("\nrayY = %f", data->ray.rayY);
	printf("\nRaymapX = %f", data->ray.mapX);
	printf("\nRaymapY = %f", data->ray.mapY);
	printf("\nsideDistX = %f", data->ray.sideDistX);
	printf("\nsideDistY = %f", data->ray.sideDistY);
	printf("\ndeltaDistX = %f", data->ray.deltaDistX);
	printf("\ndeltaDistY = %f", data->ray.deltaDistY);
	printf("\nperpWallDist = %f", data->ray.perpWallDist);
	printf("\nstepX = %d", data->ray.stepX);
	printf("\nstepY = %d", data->ray.stepY);
	printf("\nhit = %d", data->ray.hit);
	printf("\nside = %d", data->ray.side);
	while (i < data->map.Height)
	{
		j = 0;
		if (i <= 9)
			printf("\nmap [ %d] : >", i);
		else
			printf("\nmap [%d] : >", i);
		while (j < (int)ft_strlen(data->map.map[i]))
		{
			if (i == (int)data->map.pos_y && j == (int)data->map.pos_x)
			{
				printf("P ");
			}
			else
			printf("%c ", data->map.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	printf("\n\n");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
int		render_texture(t_data *data)
{
	int	x;
	int	y;
	
//	init_ray(data, &data->ray);
	update_image(data);
	x = 0;
	while (x < data->NO.tw)
	{
		y = 0;
		while (y < data->NO.th)
		{
			int color = 889568;
			my_mlx_pixel_put(&data->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
*/

int		main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	//histoire du --save en bmp a faire
//	data.mlx = mlx_init();
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
	//	mlx_loop_hook(data->mlx, render_next_frame, data);
	//	mlx_hook(data.win, 17, 1L << 17, red_cross, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
//	ft_putstr_fd("LOOP HOOK OVER\n", 1);
//	print_params(&data);
//	mlx_loop_hook(data.mlx, render_texture, &data);
	mlx_loop(data.mlx);//permet a la fenetre de rester ouverte
	//penser a enlever le fsanitize du makefile
	return (0);
}
