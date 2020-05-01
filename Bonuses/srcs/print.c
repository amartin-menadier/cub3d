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
/*
void	print_life_bar_data(t_data *data)
{
	printf("\n-- BAR_LIsetE_DATA --");
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
*/
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

void	print_set(t_data *data)//outil de verification a supprimer
{
	printf("\n-- SETTINGS --");
	printf("\nwin_size.x = %.d", data->set.win_size.x);
	printf("\nwin_size.y = %.d", data->set.win_size.y);
//	printf("\nNO_text_path = %s", data->set.NO_path);
//	printf("\nSO_text_path = %s", data->set.SO_path);
//	printf("\nWE_text_path = %s", data->set.WE_path);
//	printf("\nEA_text_path = %s", data->set.EA_path);
//	printf("\nSprite2_text_path = %s", data->set.S2_path);
//	printf("\nsetloor color = %d", data->set.floor_color);
//	printf("\nCeiling color = %d", data->set.ceiling_color);
	printf("\nMap_width = %.d", data->set.map_size.x);
	printf("\nMap_height = %.d", data->set.map_size.y);
	printf("\nNumber of sprites = %d", data->set.spr_count);
//	printf("\nPlayer started at (%.d,%d)", data->set.starting_pos.x, data->set.starting_pos.y);
//	printf("\nPlayer orientation = >%c<", data->set.player_orientation);
/*
	int i = 0;
	int j = 0;
while (i < data->set.map_size.y)
	{
		j = 0;
		if (i <= 9)
			printf("\nmap [ %d] : >", i);
		else
			printf("\nmap [%d] : >", i);
		while (j < (int)ft_strlen(data->set.map[i]))
		{
			printf("%c ", data->set.map[i][j]);
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
	printf("\nplayer is located at (%.1f;%.1f)", data->set.pos.x, data->set.pos.y);
//	printf("\ndir.x = %.15f", data->set.dir.x);
//	printf("\ndir.y = %.15f", data->set.dir.y);
//	printf("\ncamera plane.x = %.15f", data->set.plane.x);
//	printf("\ncamera plane.y = %.15f", data->set.plane.y);
}

void	print_z_buffer(t_data *data)
{
	int i = 0;

	while (i < (int)data->set.win_size.x)
	{
		if (i % 10 == 0)
		printf("%f ", data->set.z_buffer[i]);
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

	ray.x = data->set.ray.x;
	ray.y = data->set.ray.y;
	printf("\n-- RAY --");
//	printf("\ncameraX = %.15f", data->set.camera_x);
	if (data->set.ray.x >= 0)
		printf("\nray.x = +%.15f", data->set.ray.x);
	else
		printf("\nray.x = %.15f", data->set.ray.x);
	if (data->set.ray.y >= 0)
		printf("\nray.y = +%.15f", data->set.ray.y);
	else
		printf("\nray.y = %.15f", data->set.ray.y);
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
//	printf("\nstep.x = %.d", data->set.step.x);
//	printf("\nstep.y = %.d", data->set.step.y);
//	printf("\ndelta_dist.x = %.2f", data->set.delta_dist.x);
//	printf("\ndelta_dist.y = %.2f", data->set.delta_dist.y);
//	printf("\nside_dist.x = %.2f", data->set.side_dist.x);
//	printf("\nside_dist.y = %.2f", data->set.side_dist.y);
//	printf("\n(map.x;map.y) = (%.2f, %.2f)", data->set.map.x, data->set.map.y);
//	printf("\n(map.x;map.y) value = %c (char)", data->set.map[(int)data->set.map.y][(int)data->set.map.x]);
//	printf("\nside = %d", data->set.side);
//	printf("\nperp_wall_dist = %.2f", data->set.perp_wall_dist);
//	printf("\nline_height = %d", data->set.line_height);
//	printf("\ndraw_start = %d", data->set.draw_start);
//	printf("\ndraw_end = %d", data->set.draw_end);
*/
	printf("\n----");
}
void	print_current_sprite_data(t_data *data)
{
	t_set *set;

	set = &data->set;
//	printf("\nset->text.x = %d", set->text.x);
//	printf("\nset->text.y = %d", set->text.y);
//	printf("\nset->spr_inv.x = %.2f", set->spr_inv.x);
//	printf("\nset->spr_inv.y = %.2f", set->spr_inv.y);
//	printf("\nset->spr_size.x = %d", set->spr_size.x);
//	printf("\nset->spr_size.y = %d", set->spr_size.y);
//	printf("\nset->spr_draw_start.x = %d", set->spr_draw_start.x);
//	printf("\nset->spr_draw_start.y = %d", set->spr_draw_start.y);
//	printf("\nset->spr_draw_end.x = %d", set->spr_draw_end.x);
//	printf("\nset->spr_draw_end.y = %d", set->spr_draw_end.y);
//	printf("\nset->spr_screen_x = %.2f", set->spr_screen_x);
}

void	print_sprite_list(t_data *data)
{
	int	i = 0;
//	int j = 0;
	
	ft_putstr_fd("\n  -- SPRITES --\n-----------------", 1);
	while(i < data->set.spr_count)
//	|| j < data->set.spr_count)
	{
	//	if (j == data->set.spr_order[i])
		{
			printf("\nsprite[%d] = (%.1f, %.1f)", i,
					data->set.spr[i].x,
					data->set.spr[i].y);
	//				data->set.spr[i].nb);
	//		printf("\nsprdist[%d]= >%.2f<", i, data->set.spr_dist[i]);
			/*
			printf("\nspriteX = >%.1f<", data->set.spriteX);
			printf("\nspriteY = >%.1f<", data->set.spriteY);
			   printf("\ninvDet = >%f<", data->set.invDet);
			   printf("\ntransfX = >%f<", data->set.transfX);
			   printf("\ntransfY = >%f<", data->set.transfY);
			   printf("\nspriteScreenX = >%d<", data->set.spriteScreenX);
			   printf("\nspriteHeight = >%d<", data->set.spriteHeight);
			   printf("\nspriteWidth = >%d<", data->set.spriteWidth);
			   printf("\ndraw_startX = >%d<", data->set.draw_startX);
			   printf("\ndraw_endX = >%d<", data->set.draw_endX);
			   printf("\ndraw_startY = >%d<", data->set.draw_startY);
			   printf("\ndraw_endY = >%d<", data->set.draw_endY);
			   */
	//		j++;
	//		i = - 1;
		}
		i++;
	}
	printf("\n");
}

/*
void	print_map(t_data *data)
{
	int i = - 1;
	int j = 0;

	while (i < data->set.map_size.y)
	{
		j = 0;
		if (i == -1)
		{
			printf("\n             ");
			while (j < data->set.map_size.x)
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
		while (j < (int)ft_strlen(data->set.map[i]))
		{
			if (i == (int)data->set.pos.y && j == (int)data->set.pos.x)
			{
				if (data->set.dir.y <= 0 && (fabs(data->set.dir.y) > fabs(data->set.dir.x)))
					printf("P^");
				else if (data->set.dir.x >= 0  && (data->set.dir.x > fabs(data->set.dir.y)))
					printf("P>");
				else if (data->set.dir.y >= 0  && (data->set.dir.y > fabs(data->set.dir.x)))
					printf("Pv");
				else if (data->set.dir.x <= 0  && (fabs(data->set.dir.x) > fabs(data->set.dir.y)))
					printf("<P");
				else
					printf("ERROR");
			}
//			else if (i == (int)data->set.first_map.y && j == (int)data->set.first_map.x)
//				printf("r%c", data->set.map[i][j]);
//			else if (i == (int)data->set.map.y && j == (int)data->set.map.x)
//				printf("R%c", data->set.map[i][j]);
			else if (data->set.map[i][j] == '0') 
				printf("  ");
			else if (data->set.map[i][j] == '1') 
				printf("[]");
			else if (data->set.map[i][j] == '2') 
				printf("* ");
			else
				printf("%c ", data->set.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	printf("\n");
}*/
