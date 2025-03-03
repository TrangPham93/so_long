/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/03/03 11:38:21 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;

	data.game = &game;
	if (ac != 2)
		handle_error("No map is chosen", NULL);
	init_data(&data);
	read_map(av[1], &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		free_arr(game.map, game.row_count);
		handle_error("Failed to initialize Mlx", NULL);
	}
	load_window(&data);
	load_asset(&data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	render_image(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

void	init_data(t_data *data)
{
	data->game->col_count = 0;
	data->game->row_count = 0;
	data->game->collectible_count = 0;
	data->game->exit_count = 0;
	data->game->player_count = 0;
	data->game->total_collect = 0;
	data->game->total_move = 0;
}

void	load_asset(t_data *data)
{
	int	img_height;
	int	img_width;

	img_height = IMG_H;
	img_width = IMG_W;
	data->img_background = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/tiles.xpm", &img_width, &img_height);
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall.xpm",
			&img_width, &img_height);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/cow.xpm",
			&img_width, &img_height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/exit.xpm",
			&img_width, &img_height);
	data->img_collects = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/milk.xpm", &img_width, &img_height);
	if (!data->img_exit || !data->img_collects || !data->img_player
		|| !data->img_wall || !data->img_background)
	{
		on_destroy(data);
		handle_error("Failed to load image", NULL);
	}
}
