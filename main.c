/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/03/07 13:10:29 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;

	data.game = &game;
	if (ac != 2)
	{
		handle_error("No map is chosen", NULL);
		exit(-1);
	}
	init_data(&data);
	read_map(av[1], &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		free_arr(game.map, game.row_count);
		game.map = NULL;
		handle_error("Failed to initialize Mlx", NULL);
	}
	load_window(&data);
	load_asset(&data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &destroy, &data);
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
	data->win_size.x = 0;
	data->win_size.y = 0;
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
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/cow.xpm", &img_width, &img_height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/exit.xpm",
			&img_width, &img_height);
	data->img_collects = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/milk.xpm", &img_width, &img_height);
	if (!data->img_exit || !data->img_collects || !data->img_player
		|| !data->img_wall || !data->img_background)
	{
		handle_error("Failed to load textures", NULL);
		destroy(data);
	}
}

int	on_keypress(int keycode, t_data *data)
{
	if (keycode == AU || keycode == W)
		move_player(data, data->game->player.x, data->game->player.y - 1);
	else if (keycode == AD || keycode == S)
		move_player(data, data->game->player.x, data->game->player.y + 1);
	else if (keycode == AL || keycode == A)
		move_player(data, data->game->player.x - 1, data->game->player.y);
	else if (keycode == AR || keycode == D)
		move_player(data, data->game->player.x + 1, data->game->player.y);
	else if (keycode == ESC)
		destroy(data);
	return (0);
}

int	destroy(t_data *data)
{
	if (data->game->map)
	{
		free_arr(data->game->map, data->game->row_count);
		data->game->map = NULL;
	}
	if (data->mlx_ptr && data->img_background)
		mlx_destroy_image(data->mlx_ptr, data->img_background);
	if (data->mlx_ptr && data->img_collects)
		mlx_destroy_image(data->mlx_ptr, data->img_collects);
	if (data->mlx_ptr && data->img_exit)
		mlx_destroy_image(data->mlx_ptr, data->img_exit);
	if (data->mlx_ptr && data->img_player)
		mlx_destroy_image(data->mlx_ptr, data->img_player);
	if (data->mlx_ptr && data->img_wall)
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
	if (data->mlx_ptr && data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	ft_free(data->mlx_ptr);
	exit(0);
}
