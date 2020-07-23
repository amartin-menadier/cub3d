/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scripts_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/23 20:54:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void
	draw_script_mask(t_data *data, t_int win_size, int option)
{
	t_int	win;
	int		draw_start_y;

	if (option == DRAW_START)
		draw_start_y = 30;
	else
		draw_start_y = 3 * win_size.y / 4;
	win.x = 30;
	while (win.x < win_size.x - 30)
	{
		win.y = draw_start_y;
		while (win.y < win_size.y - 30)
		{
			if (win.x <= 31 || win.x >= win_size.x - 32
				|| win.y <= draw_start_y + 1 || win.y >= win_size.y - 32)
				put_pixel(&data->win, win, BLUE);
			else if (win.x == 32 || win.x == win_size.x - 33
				|| win.y == draw_start_y + 2 || win.y == win_size.y - 33)
				put_pixel(&data->win, win, WHITE);
			else
				put_pixel(&data->win, win, GREY);
			win.y++;
		}
		win.x++;
	}
}

char
	*start_message(void)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin("WELCOME TO GAMINET ! \\o/\n\nThe rules of the game ",
		"are quite simple:\nYour goal is to find Norminet, stuck ");
	str = ft_strjoin(tmp, "somewhere in the school. :(\nFollow 42 rules ");
	free(tmp);
	tmp = ft_strjoin(str, "or you might get hours of community service ");
	free(str);
	str = ft_strjoin(tmp, "(TIG) O.O\nAvoid viruses if you do not want to");
	free(tmp);
	tmp = ft_strjoin(str, " get hurt. If you are not cautious enough, ");
	free(str);
	str = ft_strjoin(tmp, "toilet paper rolls will heal you a bit. :)\n\n");
	free(tmp);
	tmp = ft_strjoin(str, "KEYS:\nZQSD to move\nArrows to look ");
	free(str);
	str = ft_strjoin(tmp, "\nESC to quit the game any time\n\nGOOD LUCK!");
	free(tmp);
	tmp = ft_strjoin(str, "\n\n(press any key to continue)");
	free(str);
	str = NULL;
	return (tmp);
}

void
	write_start_message(t_data *data)
{
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5,
		BLUE, "WELCOME TO GAMINET ! \\o/");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 20,
		BLACK, "The rules of the game are quite simple: ");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 40,
		BLACK, "To win, you must find Norminet who is stuck somewhere :(");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 60,
		BLACK, "Beware of the school rules and the virus o.o");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 80,
		BLACK, "In this troubled time, toilet paper rolls are your friends ;)");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 120,
		BLUE, "KEYS:");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 140,
		BLACK, "ZQSD to move");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 160,
		BLACK, "Arrows to look and change direction");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 5 + 200,
		BLUE, "GOOD LUCK !               (press any key to start)");
}

int
	draw_script(t_data *data, int option)
{
	draw_script_mask(data, data->win.size, option);
	mlx_put_image_to_window(data->mlx, data->window, data->win.ptr, 0, 0);
	if (option == DRAW_START)
		write_start_message(data);
	if (option == SKYBOX)
	{
		mlx_string_put(data->mlx, data->window, 50, 3 * data->win.size.y / 4
			+ 25, BLUE, "OPOPOP! You know you must take the stairs ;)");
		mlx_string_put(data->mlx, data->window, 50, 3 * data->win.size.y / 4
			+ 55, BLUE, "GAME OVER");
	}
	return (0);
}
