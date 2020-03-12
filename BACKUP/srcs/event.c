/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:24:20 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/08 19:53:08 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		presskey(int keycode, t_data *data)
{
	data->keycode = keycode;
	//	render_next_frame(data); //possibilite d'utliser cela si loop_hook non utilise dans hook_event mais les images se chevauchent...
	if (keycode == ESC)
		error_exit(data, "\nEverything went well ! ", "\\o/\n");
	return (keycode);
}

int		red_cross(t_data *data)
{
	print_params(data);
	error_exit(data, "\nEverything went well ! ", "\\o/\n");
	return (0);
}

void	hook_event(t_data *data)
{
	//	ft_putstr_fd("\nI GET INTO HOOK EVENT", 1);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_hook(data->win, 2, 1L << 0, presskey, data);
	mlx_hook(data->win, 17, 1L << 17, red_cross, data);
	return ;
}
