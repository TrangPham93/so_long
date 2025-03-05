/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:51 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 14:14:14 by trpham           ###   ########.fr       */
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
		destroy(data);
	}
	data->game->player.x = new_x;
	data->game->player.y = new_y;
	data->game->total_move++;
	ft_putstr_fd("Number of movements : ", 1);
	ft_putnbr_fd(data->game->total_move, 1);
	ft_putstr_fd("\n", 1);
	render_image(data);
}

void	render_img_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_player,
		data->game->player.x * IMG_W, data->game->player.y * IMG_H);
}

int	one_player(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < (*game).row_count - 1)
	{
		j = 1;
		while (j < (*game).col_count - 1)
		{
			if ((game->map)[i][j] == 'P')
			{
				(*game).player_count++;
				game->player.y = i;
				game->player.x = j;
			}
			j++;
		}
		i++;
	}
	if ((*game).player_count != 1)
	{
		handle_error("None or more than 1 player", NULL);
		return (-1);
	}
	return (0);
}
