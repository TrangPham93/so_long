/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:35 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 19:09:47 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_window(t_data *data)
{
	mlx_get_screen_size(data->mlx_ptr, &data->win_size.x, &data->win_size.y);
	if (data->game->row_count > (data->win_size.y / IMG_H - 3)
		|| data->game->col_count > (data->win_size.x / IMG_W))
	{
		free_arr(data->game->map, data->game->row_count);
		data->game->map = NULL;
		if (data->mlx_ptr)
			mlx_destroy_display(data->mlx_ptr);
		handle_error("Map is too big", data->mlx_ptr);
		exit(-1);
	}
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->game->col_count * IMG_W,
			data->game->row_count * IMG_H, "so_long");
	if (!data->mlx_win)
	{
		free_arr(data->game->map, data->game->row_count);
		data->game->map = NULL;
		if (data->mlx_ptr)
			mlx_destroy_display(data->mlx_ptr);
		ft_free(data->mlx_ptr);
		handle_error("Failed to initialize a window", NULL);
		exit(-1);
	}
}

void	render_image(t_data *data)
{
	render_img_background(data);
	render_img_exit_wall(data);
	render_img_collectibles(data);
	render_img_player(data);
}

void	render_img_background(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->game->row_count)
	{
		j = -1;
		while (++j < data->game->col_count)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_background, j * IMG_W, i * IMG_H);
		}
	}
}

void	render_img_exit_wall(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->game->row_count)
	{
		j = -1;
		while (++j < data->game->col_count)
		{
			if ((data->game->map)[i][j] == 'E')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
					data->img_exit, j * IMG_W, i * IMG_H);
			}
			else if ((data->game->map)[i][j] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
					data->img_wall, j * IMG_W, i * IMG_H);
		}
	}
}

void	render_img_collectibles(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->game->row_count)
	{
		j = -1;
		while (++j < data->game->col_count)
		{
			if ((data->game->map)[i][j] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
					data->img_collects, j * IMG_W, i * IMG_H);
		}
	}
}
