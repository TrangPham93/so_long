/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/28 16:15:25 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_keyrelease(int keycode, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keycode);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;
		
	data.game = &game;
	if (ac != 2)
		handle_error("No map is chosen");
	init_data(&data);
	read_map(av[1], &game);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		handle_error("Failed to initialize Mlx");
	load_window(&data);
	load_asset(&data);

	// data.game->total_collect = 0;
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &on_keypress , &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
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
