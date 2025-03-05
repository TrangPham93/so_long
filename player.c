/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:51 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 12:47:54 by trpham           ###   ########.fr       */
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
		on_destroy(data);
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

void	winner_print(void)
{
	ft_putstr_fd("-----------------------------------------------\n", 1);
	ft_putstr_fd("|    🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉     |\n", 1);
	ft_putstr_fd("|    You found all collectibles and exit.     |\n", 1);
	ft_putstr_fd("|        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           |\n", 1);
	ft_putstr_fd("-----------------------------------------------\n", 1);
}

void	handle_error(char *s, char *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	// exit(-1);
}

void	free_arr(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}
