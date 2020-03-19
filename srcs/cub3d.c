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

#include "cub3d.h"

void	print_params(t_data *data)//outil de verification a supprimer
{
	int i = 0;
	int j = 0;

	printf("\nwin_width = %d", data->settings.win_width);
	printf("\nwin_height = %d", data->settings.win_height);
	//	printf("\nNO_text_path = %s", data->settings.NO);
	//	printf("\nSO_text_path = %s", data->settings.SO);
	//	printf("\nWE_text_path = %s", data->settings.WE);
	//	printf("\nEA_text_path = %s", data->settings.EA);
	//	printf("\nSprite_text_path = %s", data->settings.S);
	printf("\nFloor color = %d", data->settings.Floor_color);
	printf("\nCeiling color = %d", data->settings.Ceiling_color);
	printf("\nMap_width = %d", data->settings.win_width);
	printf("\nMap_height = %d", data->settings.win_height);
	printf("\nPlayer is located at (%f,%f)", data->frame.posX, data->frame.posY);
	printf("\nPlayer orientation = >%c<", data->settings.player_orientation);
	printf("\n\n  -- RAYCASTING --\n--------------------\ndirX = %f", data->frame.dirX);
	printf("\ndirY = %f", data->frame.dirY);
	printf("\nrayX = %f", data->frame.rayX);
	printf("\nrayY = %f", data->frame.rayY);
	printf("\ncameraX = %f", data->frame.cameraX);
	printf("\ncamera planeX = %f", data->frame.planeX);
	printf("\ncamera planeY = %f", data->frame.planeY);
	printf("\ndeltaDistX = %f", data->frame.deltaDistX);
	printf("\ndeltaDistY = %f", data->frame.deltaDistY);
	printf("\nsideDistX = %f", data->frame.sideDistX);
	printf("\nsideDistY = %f", data->frame.sideDistY);
	printf("\nperpWallDist = %f", data->frame.perpWallDist);
	printf("\nstepX = %d", data->frame.stepX);
	printf("\nstepY = %d", data->frame.stepY);
	printf("\ntime = %f", data->frame.time);
	printf("\noldTime = %f", data->frame.oldTime);
	printf("\ninitvalue pos_x = %f", data->frame.posX);
	printf("\ninitvalue pos_y = %f", data->frame.posY);
	printf("\n(pos_x;pos_y) (//!\\\\char) = %c", data->settings.map[(int)data->frame.posY][(int)data->frame.posX]);
	printf("\n(pos_x;pos_y) (//!\\\\int) = %d", data->settings.map[(int)data->frame.posY][(int)data->frame.posX]);
	printf("\nmapX = %f", data->frame.mapX);
	printf("\nmapY = %f", data->frame.mapY);
	printf("\n(mapX;mapY) (//!\\\\char) = %c", data->settings.map[(int)data->frame.mapY][(int)data->frame.mapX]);
	printf("\n(mapX;mapY) (//!\\\\int) = %d", data->settings.map[(int)data->frame.mapY][(int)data->frame.mapX]);
	printf("\nhit = %d", data->frame.hit);
	printf("\nside = %d", data->frame.side);
	printf("\nlineHeight = %d", data->frame.lineHeight);
	printf("\ndrawStart = %d", data->frame.drawStart);
	printf("\ndrawEnd = %d", data->frame.drawEnd);
	while (i < data->settings.map_height)
	{
		j = 0;
		if (i <= 9)
			printf("\nmap [ %d] : >", i);
		else
			printf("\nmap [%d] : >", i);
		while (j < (int)ft_strlen(data->settings.map[i]))
		{
			printf("%c ", data->settings.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	printf("\n\n");
}

void	check_args_errors(t_data *data, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		close_program(data, "Invalid number of arguments\n", "");
	if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		close_program(data, "Second argument is not --save\n", "");
	if (ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		close_program(data, "File extension is not .cub\n", "");
	if ((data->settings.fd = open(argv[1], O_RDONLY)) == -1)
		close_program(data, "Couldn't open .cub file\n", "");
}

int		main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	//histoire du --save en bmp a faire
	parse_cub(&data);
	init_data(&data);//peut-etre remplacer par init window et ini image;
	hook_event(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);//permet a la fenetre de rester ouverte
	return (0);
}
