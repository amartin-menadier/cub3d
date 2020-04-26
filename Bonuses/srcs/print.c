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

void	print_life_bar_data(t_data *data)
{
	printf("\n-- BAR_LIFE_DATA --");
	printf("\nvalue = %d;", data->life.value);
	printf("\nsize.x = %d;", data->life.size.x);
	printf("\nsize.y = %d;", data->life.size.y);
	printf("\ndraw_start.x = %d;", data->life.draw_start.x);
	printf("\ndraw_start.y = %d;", data->life.draw_start.y);
	printf("\ndraw_end.x = %d;", data->life.draw_end.x);
	printf("\ndraw_end.y = %d;", data->life.draw_end.y);
	printf("\ncolor = %d;", data->life.color);
	printf("\n-------------------");
}

void	print_minimap_data(t_data *data)
{
	printf("\n-- MINI_MAP_DATA --");
	printf("\ncase_min.x = %.2f;", data->map.case_min.x);
	printf("\ncase_min.y = %.2f;", data->map.case_min.y);
	printf("\ncase_max.x = %.2f;", data->map.case_max.x);
	printf("\ncase_max.y = %.2f;", data->map.case_max.y);
	printf("\nsize in pixels= %d;", data->map.size);
	printf("\ncase_size = %d;", data->map.case_size);
	printf("\nmargin = %d;", data->map.margin);
	printf("\ndraw_start.x = %d;", data->map.draw_start.x);
	printf("\ndraw_start.y = %d;", data->map.draw_start.y);
	printf("\ndraw_end.x = %d;", data->map.draw_end.x);
	printf("\ndraw_end.y = %d;", data->map.draw_end.y);
	printf("\n-------------------");
}

void	print_image(t_data *data)
{
	printf("\n         bpp = >%d<", data->scr.bpp);
	printf("\n line length = >%d<", data->scr.line_length);
	printf("\n      endian = >%d<", data->scr.endian);
	printf("\nimage height = >%.d<", data->scr.size.y);
	printf("\n image width = >%.d<", data->scr.size.x);
	printf("\n colors[     0] = >%d<", data->scr.colors[0]);
	printf("\n colors[ 50000] = >%d<", data->scr.colors[50000]);
	printf("\n colors[100000] = >%d<", data->scr.colors[100000]);
	printf("\n colors[150000] = >%d<", data->scr.colors[150000]);
	printf("\n colors[200000] = >%d<", data->scr.colors[200000]);
	printf("\n-------------------");
}

void	print_settings(t_data *data)//outil de verification a supprimer
{
	printf("\n-- SETTINGS --");
	printf("\nwin_size.x = %.d", data->settings.win_size.x);
	printf("\nwin_size.y = %.d", data->settings.win_size.y);
//	printf("\nNO_text_path = %s", data->settings.NO_path);
//	printf("\nSO_text_path = %s", data->settings.SO_path);
//	printf("\nWE_text_path = %s", data->settings.WE_path);
//	printf("\nEA_text_path = %s", data->settings.EA_path);
//	printf("\nSprite2_text_path = %s", data->settings.S2_path);
//	printf("\nFloor color = %d", data->settings.floor_color);
//	printf("\nCeiling color = %d", data->settings.ceiling_color);
	printf("\nMap_width = %.d", data->settings.map_size.x);
	printf("\nMap_height = %.d", data->settings.map_size.y);
	printf("\nNumber of sprites = %d", data->settings.spr_count);
	printf("\nPlayer started at (%.d,%d)", data->settings.starting_pos.x, data->settings.starting_pos.y);
	printf("\nPlayer orientation = >%c<", data->settings.player_orientation);
/*
	int i = 0;
	int j = 0;
while (i < data->settings.map_size.y)
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
	printf("\nplayer is located at (%.1f;%.1f)", data->frame.pos.x, data->frame.pos.y);
	printf("\ndir.x = %.15f", data->frame.dir.x);
	printf("\ndir.y = %.15f", data->frame.dir.y);
	printf("\ncamera plane.x = %.15f", data->frame.plane.x);
	printf("\ncamera plane.y = %.15f", data->frame.plane.y);
}

void	print_z_buffer(t_data *data)
{
	int i = 0;

	while (i < (int)data->settings.win_size.x)
	{
		if (i % 10 == 0)
		printf("%f ", data->frame.z_buffer[i]);
		if (i % 50 == 0)
		printf("\n");
		i++;
	}
}

void	print_ray(t_data* data)
{
(void)data;
/*
	t_dbl	ray;

	ray.x = data->frame.ray.x;
	ray.y = data->frame.ray.y;
	printf("\n-- RAY --");
//	printf("\ncameraX = %.15f", data->frame.camera_x);
	if (data->frame.ray.x >= 0)
		printf("\nray.x = +%.15f", data->frame.ray.x);
	else
		printf("\nray.x = %.15f", data->frame.ray.x);
	if (data->frame.ray.y >= 0)
		printf("\nray.y = +%.15f", data->frame.ray.y);
	else
		printf("\nray.y = %.15f", data->frame.ray.y);
	if (fabs(ray.x) - fabs(ray.y) < 0 && ray.y > 0)
		printf("\nray to the NORTH");
	else if (fabs(ray.x) - fabs(ray.y) > 0 && ray.x > 0)
		printf("\nray to the EAST");
	else if (fabs(ray.x) - fabs(ray.y) < 0 && ray.y > 0)
		printf("\nray to the SOUTH");
	else if (fabs(ray.x) - fabs(ray.y) > 0 && ray.x < 0)
		printf("\nray to the WEST");
	else
		printf("\nray between two cardinal directions");
//	printf("\nstep.x = %.d", data->frame.step.x);
//	printf("\nstep.y = %.d", data->frame.step.y);
//	printf("\ndelta_dist.x = %.2f", data->frame.delta_dist.x);
//	printf("\ndelta_dist.y = %.2f", data->frame.delta_dist.y);
//	printf("\nside_dist.x = %.2f", data->frame.side_dist.x);
//	printf("\nside_dist.y = %.2f", data->frame.side_dist.y);
//	printf("\n(map.x;map.y) = (%.2f, %.2f)", data->frame.map.x, data->frame.map.y);
//	printf("\n(map.x;map.y) value = %c (char)", data->settings.map[(int)data->frame.map.y][(int)data->frame.map.x]);
//	printf("\nside = %d", data->frame.side);
//	printf("\nperp_wall_dist = %.2f", data->frame.perp_wall_dist);
//	printf("\nline_height = %d", data->frame.line_height);
//	printf("\ndraw_start = %d", data->frame.draw_start);
//	printf("\ndraw_end = %d", data->frame.draw_end);
*/
	printf("\n----");
}
void	print_current_sprite_data(t_data *data)
{
	t_frame *F;

	F = &data->frame;
//	printf("\nF->text.x = %d", F->text.x);
//	printf("\nF->text.y = %d", F->text.y);
	printf("\nF->spr_inv.x = %.2f", F->spr_inv.x);
	printf("\nF->spr_inv.y = %.2f", F->spr_inv.y);
	printf("\nF->spr_size.x = %d", F->spr_size.x);
	printf("\nF->spr_size.y = %d", F->spr_size.y);
	printf("\nF->spr_draw_start.x = %d", F->spr_draw_start.x);
	printf("\nF->spr_draw_start.y = %d", F->spr_draw_start.y);
	printf("\nF->spr_draw_end.x = %d", F->spr_draw_end.x);
	printf("\nF->spr_draw_end.y = %d", F->spr_draw_end.y);
	printf("\nF->spr_screen_x = %.2f", F->spr_screen_x);

}

void	print_sprite_list(t_data *data)
{
	int	i = 0;
	int j = 0;
	
	ft_putstr_fd("\n  -- SPRITES --\n-----------------", 1);
	while(i < data->settings.spr_count || j < data->settings.spr_count)
	{
		if (j == data->frame.spr_order[i])
		{
			printf("\norder %d/sprite[%d] = (%.1f, %.1f/ text %c)", j, i,
					data->settings.spr_x[i],
					data->settings.spr_y[i],
					data->settings.spr_text[i]);
			printf("\nsprdist[%d]= >%.2f<", i, data->frame.spr_dist[i]);
			/*
			printf("\nspriteX = >%.1f<", data->frame.spriteX);
			printf("\nspriteY = >%.1f<", data->frame.spriteY);
			   printf("\ninvDet = >%f<", data->frame.invDet);
			   printf("\ntransfX = >%f<", data->frame.transfX);
			   printf("\ntransfY = >%f<", data->frame.transfY);
			   printf("\nspriteScreenX = >%d<", data->frame.spriteScreenX);
			   printf("\nspriteHeight = >%d<", data->frame.spriteHeight);
			   printf("\nspriteWidth = >%d<", data->frame.spriteWidth);
			   printf("\ndraw_startX = >%d<", data->frame.draw_startX);
			   printf("\ndraw_endX = >%d<", data->frame.draw_endX);
			   printf("\ndraw_startY = >%d<", data->frame.draw_startY);
			   printf("\ndraw_endY = >%d<", data->frame.draw_endY);
			   */
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

	while (i < data->settings.map_size.y)
	{
		j = 0;
		if (i == -1)
		{
			printf("\n             ");
			while (j < data->settings.map_size.x)
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
			if (i == (int)data->frame.pos.y && j == (int)data->frame.pos.x)
			{
				if (data->frame.dir.y <= 0 && (fabs(data->frame.dir.y) > fabs(data->frame.dir.x)))
					printf("P^");
				else if (data->frame.dir.x >= 0  && (data->frame.dir.x > fabs(data->frame.dir.y)))
					printf("P>");
				else if (data->frame.dir.y >= 0  && (data->frame.dir.y > fabs(data->frame.dir.x)))
					printf("Pv");
				else if (data->frame.dir.x <= 0  && (fabs(data->frame.dir.x) > fabs(data->frame.dir.y)))
					printf("<P");
				else
					printf("ERROR");
			}
//			else if (i == (int)data->frame.first_map.y && j == (int)data->frame.first_map.x)
//				printf("r%c", data->settings.map[i][j]);
//			else if (i == (int)data->frame.map.y && j == (int)data->frame.map.x)
//				printf("R%c", data->settings.map[i][j]);
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
