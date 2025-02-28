/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:07 by trpham            #+#    #+#             */
/*   Updated: 2025/02/28 21:36:10 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		on_destroy((void *)data);
	return (0);
}

int	on_destroy(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_map(data);
	free_mlx(data);
	exit(0);
	return (0);
}
