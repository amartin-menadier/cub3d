/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprites(t_data *data, t_settings *settings, t_frame *frame, t_img *textimg)
{
	int i;
	int	j;
	t_frame *F;
	t_settings *S;

	F = frame;
	S = settings;
	i = 0;
	j = 0;

	while (i< settings->numSprites || j < settings->numSprites)
	{
		if (j == F->spriteorder[i])
		{
			//translate sprite position to relative to camera
			F->spriteX = settings->spritex[i] - F->posX;
			F->spriteY = settings->spritey[i] - F->posY;
			//	print_sprites(data);//a supprimer. Fonction de verification
			F->invDet = 1.0 / (F->planeX * F->dirY - F->dirX * F->planeY);
			F->transfX = F->invDet * (F->dirY * F->spriteX - F->dirX * F->spriteY);
			F->transfY = F->invDet * (F->planeX * F->spriteY - F->planeY * F->spriteX);
			F->spriteScreenX = (int)((S->win_width / 2) * (1 + F->transfX / F->transfY));
			F->spriteHeight = abs((int)(settings->win_height / (F->transfY)));
			F->drawStartY = -F->spriteHeight / 2 + settings->win_height / 2;
			if(F->drawStartY < 0) 
				F->drawStartY = 0;
			F->drawEndY = F->spriteHeight / 2 + settings->win_height / 2;
			if(F->drawEndY >= settings->win_height)
				F->drawEndY = settings->win_height - 1;
			F->spriteWidth = abs((int)(settings->win_height / (F->transfY)));
			F->drawStartX = -F->spriteWidth / 2 + F->spriteScreenX;
			if(F->drawStartX < 0) 
				F->drawStartX = 0;
			F->drawEndX = F->spriteWidth / 2 + F->spriteScreenX;
			if(F->drawEndX >= settings->win_width)
				F->drawEndX = settings->win_width - 1;
			int		stripe;
			int		y;
			int		d;
			stripe = F->drawStartX;
			while (stripe < F->drawEndX)
			{
				F->texX = (int)(256 * (stripe - (-F->spriteWidth / 2 
								+ F->spriteScreenX)) * textimg->tw / F->spriteWidth) / 256;
				if(F->transfY > 0 && stripe > 0 && stripe < settings->win_width && F->transfY < F->Zbuffer[stripe])
				{
					y = F->drawStartY;
					while(y < F->drawEndY)
					{
						d = (y) * 256 - settings->win_height * 128 + F->spriteHeight * 128;
						F->texY = ((d * textimg->th) / F->spriteHeight) / 256;

						if ((textimg->colors[textimg->th * F->texY + F->texX] & 0x00FFFFFF) != 0)
							my_mlx_pixel_put(&data->img, stripe, y,
									textimg->colors[textimg->th * F->texY + F->texX]);
						//		   Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
						//		   if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color

						y++;
					}
				}
				stripe++;
			}
			j++;
			i = -1;
		}
		i++;
		/*
		if (i == settings->numSprites && j < settings->numSprites)
			i = 0;
			*/
		//		(void)data;
		//	(void)textimg;

	}
}

void	sort_sprites(t_data *data, t_settings *settings, t_frame *frame)
{
	int		i;
	int		j;
	int		k;
	int		tmporder;
	t_frame *F = frame;

	i = 0;
	while (i < settings->numSprites && !F->sprites_sorted)
	{
		frame->spriteorder[i] = i;
		frame->spritedist[i] = ((frame->posX - settings->spritex[i]) *
				(frame->posX - settings->spritex[i]) + (frame->posY -
					settings->spritey[i]) * (frame->posY - settings->spritey[i]));
		i++;
	}
	/*
	   i = 0;
	   while (i<settings->numSprites && !F->sprites_sorted)
	   {
	   if (settings->spritetext[F->spriteorder[i]] == '2')//a supprimer a terme
	   {
	   if (i == 0)
	   printf("\nBEFORE SORTING");
	   if (i == 0)
	   printf("\nsprites_sorted = >%d<", F->sprites_sorted);
	   printf("\nspriteorder[%d] = >%d< ", i, F->spriteorder[i]);
	   printf("\nspritex[%d] = >%.1f< ", i, settings->spritex[i]);
	   printf("\nspritey[%d] = >%.1f< ", i, settings->spritey[i]);
	   printf("\nspritedist[%d] = >%.2f< ", i, F->spritedist[i]);
	   if (i == settings->numSprites -1)
	   printf("\n---------");
	   settings->spritetext[F->spriteorder[i]]++;//a supprimer. Fonction de verification
	   }
	   i++;
	   }

	   int x;
	   */
	i = 0;
	while (i < settings->numSprites - 1)
	{
		k = 0;
		j = i + 1;
		while (j < settings->numSprites)
		{
			if ((frame->spritedist[i] < frame->spritedist[j] && 
						frame->spriteorder[i] < frame->spriteorder[j]) || 
					(frame->spritedist[i] > frame->spritedist[j] && 
					 frame->spriteorder[i] > frame->spriteorder[j]))
			{
				k++;
				/*
				   x = i;
				   i = 0;
				   while (i<settings->numSprites)
				   {
				   if (settings->spritetext[F->spriteorder[i]] < '9')//a supprimer a terme
				   {
				   if (i== 0)
				   printf("\ni=>%d<", x);
				   if (i== 0)
				   printf("\nj=>%d<", j);
				   if (i== 0)
				   printf("\nk=>%d<", k);
				   if (i== 0)
				   printf("\nsprites_sorted = >%d<", F->sprites_sorted);
				   printf("\nspriteorder[%d] = >%d< ", i, F->spriteorder[i]);
				   printf("\nspritex[%d] = >%.1f< ", i, settings->spritex[i]);
				   printf("\nspritey[%d] = >%.1f< ", i, settings->spritey[i]);
				   printf("\nspritedist[%d] = >%.2f< ", i, F->spritedist[i]);
				   settings->spritetext[F->spriteorder[i]]++;//a supprimer. Fonction de verification
				   if (i == settings->numSprites - 1)
				   printf("\nCHANGING");
				   }
				   i++;
				   }
				   i = x;
				   */
				tmporder = frame->spriteorder[i];
				frame->spriteorder[i] = frame->spriteorder[j];
				frame->spriteorder[j] = tmporder;
				/*
				   i = 0;
				   while (i<settings->numSprites)
				   {
				   if (settings->spritetext[F->spriteorder[i]] < '9')//a supprimer a terme
				   {
				   printf("\nspriteorder[%d] = >%d< ", i, F->spriteorder[i]);
				   printf("\nspritex[%d] = >%.1f< ", i, settings->spritex[i]);
				   printf("\nspritey[%d] = >%.1f< ", i, settings->spritey[i]);
				   printf("\nspritedist[%d] = >%.2f< ", i, F->spritedist[i]);
				   settings->spritetext[F->spriteorder[i]]++;//a supprimer. Fonction de verification
				   if (i == settings->numSprites - 1)
				   printf("\n---------");
				   }
				   i++;
				   }
				   i = x;
				   */
			}
			j++;
		}
		if (k == 0)
			i++;
	}
	/*
	   i = 0;
	   while (i<settings->numSprites && !frame->sprites_sorted)
	   {
	   if (settings->spritetext[F->spriteorder[i]] < '9')//a supprimer a terme
	   {
	   printf("\nspriteorder[%d] = >%d< ", i, F->spriteorder[i]);
	//	printf("\nspritex[%d] = >%.1f< ", i, settings->spritex[i]);
	//	printf("\nspritey[%d] = >%.1f< ", i, settings->spritey[i]);
	printf("\nspritedist[%d] = >%.2f< ", i, F->spritedist[i]);
	settings->spritetext[F->spriteorder[i]]++;//a supprimer. Fonction de verification
	if (i == settings->numSprites - 1)
	printf("\n---------");
	}
	i++;
	}
	*/
	frame->sprites_sorted++;

	(void)data;
}

void	draw_column(t_data *data, t_frame *frame, t_img *textimg, int x)
{
	int		y;
	double step;
	double texPos;

	y = 0;
	while (y < frame->drawStart)
		my_mlx_pixel_put(&data->img, x, y++, data->settings.Ceiling_color);
	step = 1.0 * textimg->th / frame->lineHeight;
	texPos = (frame->drawStart - data->settings.win_height / 2 +
			frame->lineHeight / 2) * step;
	while (y < frame->drawEnd)
	{
		frame->texY = (int)texPos & (textimg->th - 1);
		texPos += step;
		my_mlx_pixel_put(&data->img, x, y,
				textimg->colors[textimg->th * frame->texY + frame->texX]);
		y++;
	}
	while (y < data->settings.win_height)
		my_mlx_pixel_put(&data->img, x, y++, data->settings.Floor_color);
}

t_img	*pick_texture(t_frame *frame)
{
	t_img	*textimg;

	if (frame->side == 0)//EA and WE
	{
		if (frame->rayX >0)//EA
			textimg = &frame->EA_img;
		else//WE
			textimg = &frame->WE_img;
	}
	else
	{
		if (frame->rayY >0)//SO
			textimg = &frame->SO_img;
		else//NO
			textimg = &frame->NO_img;
	}
	frame->texX = (int)(frame->wallX * (double)textimg->tw);
	if(frame->side == 0 && frame->rayX > 0)
		frame->texX = textimg->tw - frame->texX - 1;
	if(frame->side == 1 && frame->rayY < 0)
		frame->texX = textimg->tw - frame->texX - 1;
	return (textimg);
}

void	set_drawing_limits(t_data *data, t_frame *frame)
{
	frame->lineHeight = abs((int)(data->settings.win_height / (frame->perpWallDist)));
	frame->drawStart = -frame->lineHeight / 2 + data->settings.win_height / 2;
	if(frame->drawStart < 0)
		frame->drawStart = 0;
	frame->drawEnd = frame->lineHeight / 2 + data->settings.win_height / 2;
	if(frame->drawEnd >= data->settings.win_height)
		frame->drawEnd = data->settings.win_height;
	if (frame->side == 0)//EA and WE
		frame->wallX = frame->posY + frame->perpWallDist * frame->rayY;
	else
		frame->wallX = frame->posX + frame->perpWallDist * frame->rayX;
	frame->wallX -= floor((frame->wallX));
}

/*
 * DDA = Digital Differential Analyser
 */

void	perform_DDA(t_data *data, t_frame *frame)
{
	frame->hit = 0;
	while (frame->hit == 0)
	{
		if(frame->sideDistX < frame->sideDistY)
		{
			frame->sideDistX += frame->deltaDistX;
			frame->mapX += frame->stepX;
			frame->side = 0;
		}
		else
		{
			frame->sideDistY += frame->deltaDistY;
			frame->mapY += frame->stepY;
			frame->side = 1;
		}
		if(data->settings.map[(int)frame->mapY][(int)frame->mapX] == '1')
			frame->hit = 1;
	}
	if(frame->side == 0)
		frame->perpWallDist = (frame->mapX - data->frame.posX +
				(1 - frame->stepX)/2)/ frame->rayX ;
	else
		frame->perpWallDist = (frame->mapY - data->frame.posY +
				(1 - frame->stepY)/2)/ frame->rayY;
}

void	get_Zbuffer(t_data *data, t_frame *frame, int x)
{
	frame->Zbuffer[x] = frame->perpWallDist;
	(void)data;
}


void	set_ray(t_data *data, t_frame *frame, int x)
{
	frame->mapX = (int)frame->posX;
	frame->mapY = (int)frame->posY;
	frame->cameraX = 2 * x /(double)data->settings.win_width - 1;
	frame->rayX = frame->dirX + frame->planeX * frame->cameraX;
	frame->rayY = frame->dirY + frame->planeY * frame->cameraX;
	frame->deltaDistX = (frame->rayY == 0) ?
		0 : ((frame->rayX == 0) ? 1 : fabs(1 / frame->rayX));
	frame->deltaDistY = (frame->rayX == 0) ?
		0 : ((frame->rayY == 0) ? 1 : fabs(1 / frame->rayY));
	if (frame->rayX < 0)
		frame->stepX = -1;
	else
		frame->stepX = 1;
	if (data->frame.rayY < 0)
		frame->stepY = -1;
	else
		frame->stepY = 1;
	if (frame->rayX < 0)
		frame->sideDistX = (frame->posX - frame->mapX) * frame->deltaDistX;
	else
		frame->sideDistX = (frame->mapX + 1.0 - frame->posX) * frame->deltaDistX;
	if (data->frame.rayY < 0)
		frame->sideDistY = (frame->posY - frame->mapY) * frame->deltaDistY;
	else
		frame->sideDistY = (frame->mapY + 1.0 - frame->posY) * frame->deltaDistY;
}

int		render_next_frame(t_data *data)
{
	int		x;
	t_img	*textimg;

	x = 0;
	while (x < data->settings.win_width)
	{
		set_ray(data, &data->frame, x);
		perform_DDA(data, &data->frame);
		get_Zbuffer(data, &data->frame, x);
		set_drawing_limits(data, &data->frame);
		textimg = pick_texture(&data->frame);
		draw_column(data, &data->frame, textimg, x);
		if (x == 0)
		{
			data->frame.first_mapX = data->frame.mapX;
			data->frame.first_mapY = data->frame.mapY;
		}
		x++;
	}
	sort_sprites(data, &data->settings, &data->frame);
	draw_sprites(data, &data->settings, &data->frame, &data->frame.Sprite_img);
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}

