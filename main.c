/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/28 21:44:19 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;
		
	data.game = &game;
	if (ac != 2)
		handle_error("No map is chosen");
	init_data(&data);
	// printf("now read maps\n");
	read_map(av[1], &game);
	// printf("read map succeed\n");
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		handle_error("Failed to initialize Mlx");
	load_window(&data);
	load_asset(&data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &on_keypress , &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
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
	load_background(data);
	render_img_exit_wall(data);
	render_img_collectibles(data);
	render_img_player(data);
	render_movement_count(data);
}
