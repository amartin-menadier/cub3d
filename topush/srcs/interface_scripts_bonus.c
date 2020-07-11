/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
				put_pixel(&data->win, win, BLACK);
			else if (win.x == 32 || win.x == win_size.x - 33
				|| win.y == draw_start_y + 2 || win.y == win_size.y - 33)
				put_pixel(&data->win, win, GREY);
			else 
				put_pixel(&data->win, win, WHITE);
			win.y++;
		}
		win.x++;
	}
}

	char *
start_message(void)
{
	char	*str = NULL;
	char	*tmp = NULL;

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
	tmp = ft_strjoin(str, "KEYS:\nZQSD to move\nArrows to look\nV to ");
	free(str);
	str = ft_strjoin(tmp, "kneel\nSPACE to jump\nP to capture the screen");
	free(tmp);
	tmp = ft_strjoin(str, "\nESC to quit the game any time\n\nGOOD LUCK!");
	free(str);
	str = ft_strjoin(tmp, "\n\n(press any key to continue)");
	free(tmp);
	tmp = NULL;	
	return (str);
}

	void
write_start_message(t_data *data)
{
	mlx_string_put(data->mlx, data->window, 516, data->win.size.y / 10, 
		RED, "WELCOME TO GAMINET ! \\o/");
	mlx_string_put(data->mlx, data->window, 460, data->win.size.y / 10 + 40, 
		BLACK, "The rules of the game are quite simple: ");
	mlx_string_put(data->mlx, data->window, 404, data->win.size.y / 10 + 80, 
		BLACK, "To win, you must find Norminet who is stuck somewhere :(");
	mlx_string_put(data->mlx, data->window, 446, data->win.size.y / 10 + 120, 
		BLACK, "Beware of the school rules and the virus o.o");
	mlx_string_put(data->mlx, data->window, 387, data->win.size.y / 10 + 160, 
		BLACK, "In this troubled time, toilet paper rolls are your friends ;)");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 10 + 240, 
		RED, "KEYS:");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 10 + 280, 
		BLACK, "ZQSD to move");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 10 + 320, 
		BLACK, "Arrows to look and change direction");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 10 + 360, 
		BLACK, "V to kneel");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 10 + 400, 
		BLACK, "SPACE to jump");
	mlx_string_put(data->mlx, data->window, 50, data->win.size.y / 10 + 440, 
		BLACK, "P to print screen in a .bmp file under ./screenshot");
	mlx_string_put(data->mlx, data->window, 558, data->win.size.y / 10 + 520, 
		RED, "GOOD LUCK !               (press any key to start)");	
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
		mlx_string_put(data->mlx, data->window, 467, 3 * data->win.size.y / 4
			+ 60, RED, "OH NO! You got caught in the elevator!");
		mlx_string_put(data->mlx, data->window, 565, 3 * data->win.size.y / 4
			+ 100, RED, "GAME OVER :'(");
	}
	return (0);
}
