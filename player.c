/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:51 by trpham            #+#    #+#             */
/*   Updated: 2025/03/02 11:34:20 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_data *data, int new_x, int new_y)
{
	char	next_location;

	next_location = data->game->map[new_y][new_x];
	if (next_location == '1' || (next_location == 'E'
			&& data->game->total_collect < data->game->collectible_count))
		return ;
	if (next_location == 'C')
	{
		data->game->total_collect++;
		data->game->map[new_y][new_x] = '0';
	}
	if (next_location == 'E'
		&& data->game->total_collect == data->game->collectible_count)
	{
		winner_print();
		on_destroy((void *)data);
	}
	data->game->player.x = new_x;
	data->game->player.y = new_y;
	data->game->total_move++;
	render_image(data);
}

void	render_movement_count(t_data *data)
{
	char	*move_text;
	int		x_text;
	int		y_text;

	x_text = 10;
	y_text = 15;
	move_text = ft_itoa(data->game->total_move);
	mlx_string_put(data->mlx_ptr, data->mlx_win, x_text, y_text, 0x000000,
		"Moves: ");
	mlx_string_put(data->mlx_ptr, data->mlx_win, x_text + 40, y_text, 0x000000,
		move_text);
	free(move_text);
}

void	render_img_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_player,
		data->game->player.x * IMG_W, data->game->player.y * IMG_H);
}
