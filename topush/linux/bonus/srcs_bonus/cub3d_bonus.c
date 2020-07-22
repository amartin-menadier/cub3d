/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/22 16:50:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

/*
**if (ft_memcmp(str, "\\o/\n", 4))
**		ft_putstr_fd("Error\n", 1);
*/

void
	close_program(t_data *data, char *error_msg, char *str)
{
	ft_putstr_fd(error_msg, 1);
	ft_putstr_fd(str, 1);
	free_all(data);
	ft_putstr_fd("\n_END_OF_PROGRAM_\n", 1);
	exit(0);
}

void
	check_args_errors(t_data *data, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		close_program(data, "Invalid number of arguments\n", "");
	if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		close_program(data, "Second argument is not --save\n", "");
	else if (argc == 3)
		data->save = 1;
	else
		data->save = 0;
	if (ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		close_program(data, "Map file name does not end with .cub\n", "");
	data->cub_path = ft_strdup(argv[1]);
}

int
	start_game(t_data *data)
{
	init_all(data);
	set_game(data);
	hook_event(data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return (0);
}

/*
**	check_args_errors(&data, argc, argv); removed
*/

int
	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	data.cub_path = ft_strdup(argv[1]);
	start_game(&data);
	return (0);
}
