/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c						                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_image(t_data *data)
{
	printf("\n         bpp = >%d<", data->img.bpp);
	printf("\n line length = >%d<", data->img.line_length);
	printf("\n      endian = >%d<", data->img.endian);
	printf("\nimage height = >%d<", data->img.th);
	printf("\n image width = >%d<", data->img.tw);
	printf("\n colors[     0] = >%d<", data->img.colors[0]);
	printf("\n colors[ 50000] = >%d<", data->img.colors[50000]);
	printf("\n colors[100000] = >%d<", data->img.colors[100000]);
	printf("\n colors[150000] = >%d<", data->img.colors[150000]);
	printf("\n colors[200000] = >%d<", data->img.colors[200000]);
	printf("\n-------------------");
}

void	print_settings(t_data *data)//outil de verification a supprimer
{
	printf("\n-- SETTINGS --");
	printf("\nwin_width = %d", data->settings.win_width);
	printf("\nwin_height = %d", data->settings.win_height);
	printf("\nNO_text_path = %s", data->settings.NO_path);
	printf("\nSO_text_path = %s", data->settings.SO_path);
	printf("\nWE_text_path = %s", data->settings.WE_path);
	printf("\nEA_text_path = %s", data->settings.EA_path);
	printf("\nSprite_text_path = %s", data->settings.Sprite_path);
	printf("\nFloor color = %d", data->settings.Floor_color);
	printf("\nCeiling color = %d", data->settings.Ceiling_color);
	printf("\nMap_width = %d", data->settings.map_width);
	printf("\nMap_height = %d", data->settings.map_height);
	printf("\nNumber of sprites = %d", data->settings.numSprites);
	printf("\nPlayer started at (%d,%d)", data->settings.init_posX, data->settings.init_posY);
	printf("\nPlayer orientation = >%c<", data->settings.player_orientation);
/*
	int i = 0;
	int j = 0;
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
	*/
	printf("\n\n");
}

void	print_situation(t_data* data)
{
	printf("\n\n  -- CURRENT SITUATION --\n--------------------");
	printf("\nplayer is located at (%.1f;%.1f)", data->frame.posX, data->frame.posY);
	printf("\ndirX = %.2f", data->frame.dirX);
	printf("\ndirY = %.2f", data->frame.dirY);
	printf("\ncamera planeX = %.2f", data->frame.planeX);
	printf("\ncamera planeY = %.2f", data->frame.planeY);
}

void	print_Zbuffer(t_data *data)
{
	int i = 0;

	while (i < data->settings.win_width)
	{
		if (i % 10 == 0)
		printf("%f ", data->frame.Zbuffer[i]);
		if (i % 50 == 0)
		printf("\n");
		i++;
	}
}

void	print_ray(t_data* data)
{
	printf("\n-- RAY --");
	printf("\ncameraX = %.2f", data->frame.cameraX);
	printf("\nrayX = %.2f", data->frame.rayX);
	printf("\nrayY = %.2f", data->frame.rayY);
	printf("\nstepX = %d", data->frame.stepX);
	printf("\nstepY = %d", data->frame.stepY);
	printf("\ndeltaDistX = %.2f", data->frame.deltaDistX);
	printf("\ndeltaDistY = %.2f", data->frame.deltaDistY);
	printf("\nsideDistX = %.2f", data->frame.sideDistX);
	printf("\nsideDistY = %.2f", data->frame.sideDistY);
	printf("\n(mapX;mapY) = (%.2f, %.2f)", data->frame.mapX, data->frame.mapY);
	printf("\n(mapX;mapY) value = %c (char)", data->settings.map[(int)data->frame.mapY][(int)data->frame.mapX]);
	printf("\nhit = %d", data->frame.hit);
	printf("\nside = %d", data->frame.side);
	printf("\nperpWallDist = %.2f", data->frame.perpWallDist);
	printf("\nlineHeight = %d", data->frame.lineHeight);
	printf("\ndrawStart = %d", data->frame.drawStart);
	printf("\ndrawEnd = %d", data->frame.drawEnd);
}


void	print_sprites(t_data *data)
{
	int	i = 0;
	int j = 0;
	
	printf("\n  -- SPRITES --\n-----------------");
	while(i < data->settings.numSprites || j < data->settings.numSprites)
	{
		if (j == data->frame.spriteorder[i])
		{
			printf("\norder %d/sprite[%d](x, y, text)= (%.1f, %.1f; %c)", j, i,
					data->settings.spritex[i],
					data->settings.spritey[i], 
					data->settings.spritetext[i]);
			printf("\nspritedist[%d]= >%.3f<", i, data->frame.spritedist[i]);
			
			   printf("\nspriteX = >%.1f<", data->frame.spriteX);
			   printf("\nspriteY = >%.1f<", data->frame.spriteY);
			   printf("\ninvDet = >%f<", data->frame.invDet);
			   printf("\ntransfX = >%f<", data->frame.transfX);
			   printf("\ntransfY = >%f<", data->frame.transfY);
			   printf("\nspriteScreenX = >%d<", data->frame.spriteScreenX);
			   printf("\nspriteHeight = >%d<", data->frame.spriteHeight);
			   printf("\nspriteWidth = >%d<", data->frame.spriteWidth);
			   printf("\ndrawStartX = >%d<", data->frame.drawStartX);
			   printf("\ndrawEndX = >%d<", data->frame.drawEndX);
			   printf("\ndrawStartY = >%d<", data->frame.drawStartY);
			   printf("\ndrawEndY = >%d<", data->frame.drawEndY);
			   
			j++;
			i = - 1;
		}
		i++;
	}
	printf("\n");
}


void	print_map(t_data *data)
{
	int i = - 1;
	int j = 0;

	while (i < data->settings.map_height)
	{
		j = 0;
		if (i == -1)
		{
			printf("\n             ");
			while (j < data->settings.map_width)
			{
				if (j < 10)
					printf("%d ", j);
				else if (j % 10 == 0)
					printf("%d", j);
				else
					printf(" %d", j%10);
				j++;
			}
			i++;
			j = 0;
		}
		if (i <= 9)
			printf("\nmap [ %d] : > ", i);
		else
			printf("\nmap [%d] : > ", i);
		while (j < (int)ft_strlen(data->settings.map[i]))
		{
			if (i == (int)data->frame.posY && j == (int)data->frame.posX)
			{
				if (data->frame.dirY <= 0 && (fabs(data->frame.dirY) > fabs(data->frame.dirX)))
					printf("P^");
				else if (data->frame.dirX >= 0  && (data->frame.dirX > fabs(data->frame.dirY)))
					printf("P>");
				else if (data->frame.dirY >= 0  && (data->frame.dirY > fabs(data->frame.dirX)))
					printf("Pv");
				else if (data->frame.dirX <= 0  && (fabs(data->frame.dirX) > fabs(data->frame.dirY)))
					printf("<P");
				else
					printf("ERROR");
			}
//			else if (i == (int)data->frame.first_mapY && j == (int)data->frame.first_mapX)
//				printf("r%c", data->settings.map[i][j]);
			else if (i == (int)data->frame.mapY && j == (int)data->frame.mapX)
				printf("R%c", data->settings.map[i][j]);
			else if (data->settings.map[i][j] == '0') 
				printf("  ");
			else if (data->settings.map[i][j] == '1') 
				printf("[]");
			else if (data->settings.map[i][j] == '2') 
				printf("* ");
			else
				printf("%c ", data->settings.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	printf("\n");
}
