/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
draw_sprite_column(t_data *data, t_frame *F, t_img *text, int stripe)
{
	t_vector	spr_img;
	t_settings	*S;
	int			d;

	spr_img.x = stripe;
	spr_img.y = F->drawStartY;
	S = &data->settings;
	F->texX = (int)(256 * (stripe - (-F->spriteWidth / 2 + F->spriteScreenX))
		* text->tw / F->spriteWidth) / 256;
	if (F->transfY >= 0 && stripe >= 0 && stripe <= S->win_width
		&& F->transfY <= F->Zbuffer[stripe])
	{
		while (spr_img.y < F->drawEndY)
		{
			d = (spr_img.y) * 256 - S->win_height * 128 + F->spriteHeight * 128;
			F->texY = ((d * text->th) / F->spriteHeight) / 256;
			if ((text->colors[text->th * F->texY + F->texX] & 0x00FFFFFF) != 0)
			{
				put_pixel(&data->img, &spr_img,
						text->colors[text->th * F->texY + F->texX]);
			}
			spr_img.y++;
		}
	}
}

	void
set_sprite_drawing_limits(t_settings *S, t_frame *F, int i)
{
	F->spriteX = S->spritex[i] - F->posX;
	F->spriteY = S->spritey[i] - F->posY;
	F->invDet = 1.0 / (F->planeX * F->dirY - F->dirX * F->planeY);
	F->transfX = F->invDet * (F->dirY * F->spriteX - F->dirX * F->spriteY);
	F->transfY = F->invDet * (F->planeX * F->spriteY - F->planeY * F->spriteX);
	F->spriteScreenX = (int)((S->win_width / 2) * (1 + F->transfX / F->transfY));
	F->spriteHeight = abs((int)(S->win_height / (F->transfY)));
	F->drawStartY = -F->spriteHeight / 2 + S->win_height / 2;
	if(F->drawStartY < 0) 
		F->drawStartY = 0;
	F->drawEndY = F->spriteHeight / 2 + S->win_height / 2;
	if(F->drawEndY >= S->win_height)
		F->drawEndY = S->win_height;
	F->spriteWidth = abs((int)(S->win_height / (F->transfY)));
	F->drawStartX = -F->spriteWidth / 2 + F->spriteScreenX;
	if(F->drawStartX < 0) 
		F->drawStartX = 0;
	F->drawEndX = F->spriteWidth / 2 + F->spriteScreenX;
	if(F->drawEndX >= S->win_width)
		F->drawEndX = S->win_width;
}

	void
draw_sprites(t_data *data, t_settings *S, t_frame *F, t_img *text)
{
	int i;
	int	j;
	int		stripe;

	i = 0;
	j = 0;
	while (i< S->numSprites || j < S->numSprites)
	{
		if (j == F->spriteorder[i] && F->spritedist[i] > 0.1)
		{
			set_sprite_drawing_limits(S, F, i);
			stripe = F->drawStartX;
			while (stripe < F->drawEndX)
			{
				draw_sprite_column(data, F, text, stripe);
				stripe++;
			}
			j++;
			i = -1;
		}
		i++;
	}
}

void	init_sprite_order(t_settings *S, t_frame *F)
{
	int i;

	i = 0;
	while (i < S->numSprites && !F->sprites_sorted)
	{
		F->spriteorder[i] = i;
		F->spritedist[i] = 
			((F->posX - S->spritex[i]) * (F->posX - S->spritex[i])
			+ (F->posY - S->spritey[i]) * (F->posY - S->spritey[i]));
		i++;
	}
}

void	sort_sprites(t_settings *settings, t_frame *frame)
{
	t_vector	at;
	int		tmporder;

	init_sprite_order(settings, frame);
	at.x = 0;
	while (at.x < settings->numSprites - 1)
	{
		at.z = 0;
		at.y = at.x;
		while (++at.y < settings->numSprites)
		{
			if ((frame->spritedist[at.x] < frame->spritedist[at.y] && 
						frame->spriteorder[at.x] < frame->spriteorder[at.y]) || 
					(frame->spritedist[at.x] > frame->spritedist[at.y] && 
					 frame->spriteorder[at.x] > frame->spriteorder[at.y]))
			{
				at.z++;
				tmporder = frame->spriteorder[at.x];
				frame->spriteorder[at.x] = frame->spriteorder[at.y];
				frame->spriteorder[at.y] = tmporder;
			}
		}
		at.x = (at.z == 0) ? at.x + 1 : at.x;
	}
	frame->sprites_sorted++;
}
