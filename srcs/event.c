/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		presskey(int keycode, t_data *data)
{
	double	oldDirX;
	double oldPlaneX;
	double	rotSpeed = 0.18;
	double	moveSpeed = 0.33;
	t_ray	*ray;

	ray = &data->ray;
	data->keycode = keycode;
	//	render_next_frame(data); //possibilite d'utliser cela si loop_hook non utilise dans hook_event mais les images se chevauchent...
	printf("\nCMD = >%d<\n", keycode);
	if (keycode == ESC)
		error_exit(data, "\nEverything went well ! ", "\\o/\n");
	if (keycode == LOOK_LEFT)
	{
		oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(-rotSpeed) - ray->dirY * sin(-rotSpeed);
		ray->dirY = oldDirX * sin(-rotSpeed) + ray->dirY * cos(-rotSpeed);
		oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(-rotSpeed) - ray->planeY * sin(-rotSpeed);
		ray->planeY = oldPlaneX * sin(-rotSpeed) + ray->planeY * cos(-rotSpeed);
	}
	if (keycode == LOOK_RIGHT)
	{
		oldDirX = ray->dirX;
		ray->dirX = ray->dirX * cos(rotSpeed) - ray->dirY * sin(rotSpeed);
		ray->dirY = oldDirX * sin(rotSpeed) + ray->dirY * cos(rotSpeed);
		oldPlaneX = ray->planeX;
		ray->planeX = ray->planeX * cos(rotSpeed) - ray->planeY * sin(rotSpeed);
		ray->planeY = oldPlaneX * sin(rotSpeed) + ray->planeY * cos(rotSpeed);
	}
	if (keycode == MOVE_FORWARD)
	{
		if(data->map.map[(int)data->map.pos_y][(int)(data->map.pos_x + ray->dirX * moveSpeed)] != 49)
			data->map.pos_x += ray->dirX * moveSpeed;
		if(data->map.map[(int)(data->map.pos_y + ray->dirY * moveSpeed)][(int)(data->map.pos_x)] != 49)
			data->map.pos_y += ray->dirY * moveSpeed;
	}
	if (keycode == MOVE_BACKWARD)
	{
		if(data->map.map[(int)data->map.pos_y][(int)(data->map.pos_x - ray->dirX * moveSpeed)] != 49)
			data->map.pos_x -= ray->dirX * moveSpeed;
		if(data->map.map[(int)(data->map.pos_y - ray->dirY * moveSpeed)][(int)data->map.pos_x] != 49)
			data->map.pos_y -= ray->dirY * moveSpeed;
	}
	if (keycode == MOVE_RIGHT)
	{
		if(data->map.map[(int)data->map.pos_y][(int)(data->map.pos_x - ray->dirY * moveSpeed)] != 49)
			data->map.pos_x -= ray->dirY * moveSpeed;
		if(data->map.map[(int)(data->map.pos_y + ray->dirX * moveSpeed)][(int)data->map.pos_x] != 49)
			data->map.pos_y += ray->dirX * moveSpeed;
	}
	if (keycode == MOVE_LEFT)
	{
		if(data->map.map[(int)data->map.pos_y][(int)(data->map.pos_x + ray->dirY * moveSpeed)] != 49)
			data->map.pos_x += ray->dirY * moveSpeed;
		if(data->map.map[(int)(data->map.pos_y - ray->dirX * moveSpeed)][(int)data->map.pos_x] != 49)
			data->map.pos_y -= ray->dirX * moveSpeed;
	}
	/*
	//move backwards if no wall behind you
	if (keyDown(SDLK_DOWN))
	{
	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
	if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	//	if (keycode == LOOK_RIGHT)
	//		error_exit(data, "\nEverything went well ! ", "\\o/\n");
	*/
	int i = 0;
	int j = 0;
	while (i < data->map.Height)
	{
		j = 0;
		if (i <= 9)
			printf("\nmap [ %d] : > ", i);
		else
			printf("\nmap [%d] : > ", i);
		while (j < (int)ft_strlen(data->map.map[i]))
		{
			if (i == (int)data->map.pos_y && j == (int)data->map.pos_x)
			{
				if (data->ray.dirY <= 0 && (fabs(data->ray.dirY) > fabs(data->ray.dirX)))
					printf("P^");
				else if (data->ray.dirX >= 0  && (data->ray.dirX > fabs(data->ray.dirY)))
					printf("P>");
				else if (data->ray.dirY >= 0  && (data->ray.dirY > fabs(data->ray.dirX)))
					printf("Pv");
				else if (data->ray.dirX <= 0  && (fabs(data->ray.dirX) > fabs(data->ray.dirY)))
					printf("<P");
				else
					printf("ERROR");
			}
			else if (i == (int)data->ray.mapY && j == (int)data->ray.mapX)
				printf("R%c", data->map.map[i][j]);
			else if (data->map.map[i][j] == '0') 
				printf("  ");
			else if (data->map.map[i][j] == '1') 
				printf("[]");
			else
				printf("%c ", data->map.map[i][j]);

			j++;
		}
		i++;
		printf("<");
	}
	//	printf("\nMap_height = %d", data->map.Height);
	printf("\npos_x = %f", data->map.pos_x);
	printf("\npos_y = %f", data->map.pos_y);
	printf("\nPlayer is located at (%f,%f)", data->map.pos_x, data->map.pos_y);
	printf("\ndirX = %f", data->ray.dirX);
	printf("\ndirY = %f", data->ray.dirY);
	printf("\nmapX = %f", data->ray.mapX);
	printf("\nmapY = %f", data->ray.mapY);
	printf("\nmap(mapY;mapX) (//!\\\\char) = %c", data->map.map[(int)data->ray.mapY][(int)data->ray.mapX]);
	printf("\nrayX = %f", data->ray.rayX);
	printf("\nrayY = %f", data->ray.rayY);
	printf("\ndeltaDistX = %f", data->ray.deltaDistX);
	printf("\ndeltaDistY = %f", data->ray.deltaDistY);
	printf("\nsideDistX = %f", data->ray.sideDistX);
	printf("\nsideDistY = %f", data->ray.sideDistY);
	printf("\nstepX = %d", data->ray.stepX);
	printf("\nstepY = %d", data->ray.stepY);
	printf("\nside = %d", data->ray.side);
	printf("\nperpWallDist = %f", data->ray.perpWallDist);
	printf("\nlineHeight = %d", data->ray.lineHeight);
	printf("\n");
	return (keycode);
}

int		red_cross(t_data *data)
{
	//	print_params(data);
	error_exit(data, "\nEverything went well ! ", "\\o/\n");
	return (0);
}

void	print_params(t_data *data)//outil de verification a supprimer
{
	int i = 0;
	int j = 0;

	printf("\nResx = %d", data->settings.Resx);
	printf("\nResy = %d", data->settings.Resy);
	//	printf("\nNO_text_path = %s", data->settings.NO);
	//	printf("\nSO_text_path = %s", data->settings.SO);
	//	printf("\nWE_text_path = %s", data->settings.WE);
	//	printf("\nEA_text_path = %s", data->settings.EA);
	//	printf("\nSprite_text_path = %s", data->settings.S);
	printf("\nFloor color = %d", data->settings.F);
	printf("\nCeiling color = %d", data->settings.C);
	printf("\nMap_width = %d", data->map.Width);
	printf("\nMap_height = %d", data->map.Height);
	printf("\nPlayer is located at (%f,%f)", data->map.pos_x, data->map.pos_y);
	printf("\nPlayer orientation = >%c<", data->map.player_orientation);
	printf("\n\n  -- RAYCASTING --\n--------------------\ndirX = %f", data->ray.dirX);
	printf("\ndirY = %f", data->ray.dirY);
	printf("\nrayX = %f", data->ray.rayX);
	printf("\nrayY = %f", data->ray.rayY);
	printf("\ncameraX = %f", data->ray.cameraX);
	printf("\ncamera planeX = %f", data->ray.planeX);
	printf("\ncamera planeY = %f", data->ray.planeY);
	printf("\ndeltaDistX = %f", data->ray.deltaDistX);
	printf("\ndeltaDistY = %f", data->ray.deltaDistY);
	printf("\nsideDistX = %f", data->ray.sideDistX);
	printf("\nsideDistY = %f", data->ray.sideDistY);
	printf("\nperpWallDist = %f", data->ray.perpWallDist);
	printf("\nstepX = %d", data->ray.stepX);
	printf("\nstepY = %d", data->ray.stepY);
	printf("\ntime = %f", data->ray.time);
	printf("\noldTime = %f", data->ray.oldTime);
	printf("\ninitvalue pos_x = %f", data->map.pos_x);
	printf("\ninitvalue pos_y = %f", data->map.pos_y);
	printf("\n(pos_x;pos_y) (//!\\\\char) = %c", data->map.map[(int)data->map.pos_y][(int)data->map.pos_x]);
	printf("\n(pos_x;pos_y) (//!\\\\int) = %d", data->map.map[(int)data->map.pos_y][(int)data->map.pos_x]);
	printf("\nmapX = %f", data->ray.mapX);
	printf("\nmapY = %f", data->ray.mapY);
	printf("\n(mapX;mapY) (//!\\\\char) = %c", data->map.map[(int)data->ray.mapY][(int)data->ray.mapX]);
	printf("\n(mapX;mapY) (//!\\\\int) = %d", data->map.map[(int)data->ray.mapY][(int)data->ray.mapX]);
	printf("\nhit = %d", data->ray.hit);
	printf("\nside = %d", data->ray.side);
	printf("\nlineHeight = %d", data->ray.lineHeight);
	printf("\ndrawStart = %d", data->ray.drawStart);
	printf("\ndrawEnd = %d", data->ray.drawEnd);
	while (i < data->map.Height)
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

int		render_next_frame(t_data *data)
{
	int	x;
	int	y;
	double	width;
	t_ray	*ray;

	ray = &data->ray;
	width = (double)data->settings.Resx;
	x = 0;
	while (x < data->settings.Resx)
		//	while (x < 2)
	{
		//init la position initiale du ray (ie, la position du player)
		ray->mapX = (int)data->map.pos_x;
		ray->mapY = (int)data->map.pos_y;


		//ramplacer la valeur de la case du joueur par '0' pas sur que ce soit utile fait dans init.
		//calcule la position de la camera sur l'ecran de -1 gauche a 1 droite
		ray->cameraX = 2 * x /(double)data->settings.Resx - 1;
		//calcule la dir (x;y) du ray. si N rayinit = (-0.66 -1) regard a gauche
		ray->rayX = ray->dirX + ray->planeX * ray->cameraX;
		ray->rayY = ray->dirY + ray->planeY * ray->cameraX;
		//calcule la distance entre deux x ou y de la map en fonction orientation du ray
		//en fait pas exactement mais conserve le ratio qui importe
		ray->deltaDistX = (ray->rayY == 0) ? 0 : ((ray->rayX == 0) ? 1 : fabs(1 / ray->rayX));
		ray->deltaDistY = (ray->rayX == 0) ? 0 : ((ray->rayY == 0) ? 1 : fabs(1 / ray->rayY));
		//sideDistX/Y = calcule la dist entre la pos init et les premiers x/yside
		//stepX/Y calcule la direction dans la carte en terme de mouvements de x ou y 1 ou -1 toujours
		if (ray->rayX < 0)
		{
			ray->stepX = -1;
			ray->sideDistX = (data->map.pos_x - ray->mapX) * ray->deltaDistX;
		}
		else
		{
			ray->stepX = 1;
			ray->sideDistX = (ray->mapX + 1.0 - data->map.pos_x) * ray->deltaDistX;
		}
		if (data->ray.rayY < 0)
		{
			ray->stepY = -1;
			ray->sideDistY = (data->map.pos_y - ray->mapY) * ray->deltaDistY;
		}
		else
		{
			ray->stepY = 1;
			ray->sideDistY = (ray->mapY + 1.0 - data->map.pos_y) * ray->deltaDistY;
		}
		data->ray.hit = 0;
		//perform DDA 
		//incremente sideDistX/Y avec deltaX/Y 
		//incremente mapX/Y avec stepX/Y
		//si mur vertical touche side = 0, si mur horizontal, side = 1
		while (data->ray.hit == 0)
		{
			/*
			   printf("\n\nWhile DDA - beggining");
			   printf("\nmap(X;Y) = map(%d,%d) = %d", (int)ray->mapX, (int)ray->mapY, data->map.map[(int)ray->mapY][(int)ray->mapX]);
			   printf("\ndeltaDistX = %f", data->ray.deltaDistX);
			   printf("\ndeltaDistY = %f", data->ray.deltaDistY);
			   printf("\nsideDistX = %f", data->ray.sideDistX);
			   printf("\nsideDistY = %f", data->ray.sideDistY);
			   */
			if(ray->sideDistX < ray->sideDistY)
			{
				ray->sideDistX += ray->deltaDistX;
				ray->mapX += ray->stepX;
				ray->side = 0;
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				ray->mapY += ray->stepY;
				ray->side = 1;
			}
			//	printf("MAIN POS E\n");
			if(data->map.map[(int)ray->mapY][(int)ray->mapX] > '0')
				ray->hit = 1;
		}
		/*
		   printf("\n\nAfter DDA");
		   printf("\nmap(X;Y) = map(%f;%f) = %d", ray->mapX, ray->mapY, data->map.map[(int)ray->mapY][(int)ray->mapX]);
		   printf("\nmap(X;Y) = map(%d,%d) = %d", (int)ray->mapX, (int)ray->mapY, data->map.map[(int)ray->mapY][(int)ray->mapX]);
		   printf("\ndeltaDistX = %f", data->ray.deltaDistX);
		   printf("\ndeltaDistY = %f", data->ray.deltaDistY);
		   printf("\nsideDistX = %f", data->ray.sideDistX);
		   printf("\nsideDistY = %f\n\n", data->ray.sideDistY);
		   */
		//	printf("MAIN POS E2\n");
		//calculate distance to wall

		if(ray->side == 0)
			ray->perpWallDist = (ray->mapX - data->map.pos_x + (1 - ray->stepX)/2)/ ray->rayX ;
		else
			ray->perpWallDist = (ray->mapY - data->map.pos_y + (1 - ray->stepY)/2)/ ray->rayY;
		//		print_params(data);
		//	printf("MAIN POS F\n");
		//Calculate height of line to draw on screen
		if (ray->perpWallDist < 1)
			ray->lineHeight = data->settings.Resy;
		else
			ray->lineHeight = abs((int)(data->settings.Resy / (ray->perpWallDist)));

		//	printf("MAIN POS G\n");
		//calculate lowest and highest pixel to fill in current stripe
		ray->drawStart = -ray->lineHeight / 2 + data->settings.Resy / 2;
		if(ray->drawStart < 0)
			ray->drawStart = 0;
		ray->drawEnd = ray->lineHeight / 2 + data->settings.Resy / 2;
		if(ray->drawEnd >= data->settings.Resy)
			ray->drawEnd = data->settings.Resy;


		//	int *texture = NULL;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		int tw;
		int th;
		int  *colors;
		if (ray->side == 0)//EA and WE
		{
			wallX = data->map.pos_y + ray->perpWallDist * ray->rayY;
			if (ray->rayX >0)//EA
			{
		tw = data->settings.EA.tw;
		th = data->settings.EA.th;
		colors = data->settings.EA.colors;
			}
			else//WE
			{
		tw = data->settings.WE.tw;
		th = data->settings.WE.th;
		colors = data->settings.WE.colors;
			}
		}
		else
		{
			wallX = data->map.pos_x + ray->perpWallDist * ray->rayX;
			if (ray->rayY >0)//SO
			{
		tw = data->settings.SO.tw;
		th = data->settings.SO.th;
		colors = data->settings.SO.colors;
			}
			else//NO
			{
		tw = data->settings.NO.tw;
		th = data->settings.NO.th;
		colors = data->settings.NO.colors;
			}
		}
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)tw);
		if(ray->side == 0 && ray->rayX > 0)
			texX = tw - texX - 1;
		if(ray->side == 1 && ray->rayY < 0)
			texX = tw - texX - 1;

		//	printf("MAIN POS H\n");
		/*
		int color;
		if (ray->side == 1)
		{
			if (ray->rayY < 0)
				//color = ray->NO;
				color = 11022898;
			else
				color = 8002588;
			//	color = ray->SO;
		}
		else	
		{
			if (ray->rayX > 0)
				color = 8002588;
			//color = ray->EA;
			else
				color = 11022898;
			//	color = ray->WE;
		}
		*/

		y = 0;
		while (y < data->ray.drawStart)
		{
			my_mlx_pixel_put(&data->img, x, y, data->settings.C);
			y++;
		}

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * th / ray->lineHeight;
		// Starting texture coordinate
		double texPos = (data->ray.drawStart - data->settings.Resy / 2 + ray->lineHeight / 2) * step;

		while (y < data->ray.drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (th - 1);
		texPos += step;
		int color = colors[th * texY + texX];
			//	buffer[y][x] = color;

			my_mlx_pixel_put(&data->img, x, y, color);
			y++;
		}
		while (y < data->settings.Resy)
		{
			my_mlx_pixel_put(&data->img, x, y, data->settings.F);
			y++;
		}
		//	printf("MAIN POS Y\n");
		//	printf("\ny is = >%d<\n", y);
		//	printf("x is = >%d<\n", x);
		//	printf("cameraX = %f\n", data->ray.cameraX);
		x++;
		if (x == 1 && ray->time == 0)
		{
			ray->time++;
			printf("\n Debut du raycasting");
			int i = 0;
			int j = 0;
			while (i < data->map.Height)
			{
				j = 0;
				if (i <= 9)
					printf("\nmap [ %d] : > ", i);
				else
					printf("\nmap [%d] : > ", i);
				while (j < (int)ft_strlen(data->map.map[i]))
				{
					if (i == (int)data->map.pos_y && j == (int)data->map.pos_x)
					{
						if (data->ray.dirY <= 0 && (fabs(data->ray.dirY) > fabs(data->ray.dirX)))
							printf("P^");
						else if (data->ray.dirX >= 0  && (data->ray.dirX > fabs(data->ray.dirY)))
							printf("P>");
						else if (data->ray.dirY >= 0  && (data->ray.dirY > fabs(data->ray.dirX)))
							printf("Pv");
						else if (data->ray.dirX <= 0  && (fabs(data->ray.dirX) > fabs(data->ray.dirY)))
							printf("<P");
						else
							printf("ERROR");
					}
					else if (i == (int)data->ray.mapY && j == (int)data->ray.mapX)
						printf("r%c", data->map.map[i][j]);
					else if (data->map.map[i][j] == '0') 
						printf("  ");
					else if (data->map.map[i][j] == '1') 
						printf("[]");
					else
						printf("%c ", data->map.map[i][j]);

					j++;
				}
				i++;
				printf("<");
			}
		}

	}
	//	printf("x = %d\n", x);
	//	printf("y = %d\n", y);
	//	print_params(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
/*
	render_texture(data);
	mlx_put_image_to_window(data->mlx, data->win, data->NO.img, 0, 0);
*/
	//	mlx_hook(data->win, 2, 1L << 0, presskey, data);

	return (0);
}

void	hook_event(t_data *data)
{
	//	ft_putstr_fd("\nI GET INTO HOOK EVENT", 1);
	mlx_hook(data->win, 2, 1L << 0, presskey, data);
	//	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_hook(data->win, 17, 1L << 17, red_cross, data);
	return ;
}
