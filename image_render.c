/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:35 by trpham            #+#    #+#             */
/*   Updated: 2025/02/20 19:58:58 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	load_window(t_data *data, t_game *game)
{
	data->mlx_win = mlx_new_window(data->mlx_ptr, game->col_count * 32,
		game->row_count * 32 , "so_long");
	if (!data->mlx_win)
		handle_error("Failed to initialize a window");
}

void	load_background(t_data *data, t_game *game)
{
	char	*relative_path = "./images/empty_space.xpm";
	int		img_height = 32;
	int 	img_width = 32;
	int		i;
	int		j;
	
	data->img_background = mlx_xpm_file_to_image(data->mlx_ptr, relative_path,
		&img_width, &img_height);
	if (!data->img_background)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_background);
		handle_error("Failed to load image");
	}
	i = -1;
	while (++i < game->row_count)
	{
		j = -1;
		while (++j < game->col_count)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_background, j * 32, i * 32);
		}
	}
}

void	load_images(t_data *data)
{
	int		img_height = 32;
	int 	img_width = 32;
	
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
		"./images/wall.xpm", &img_width, &img_height);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
		"./images/cow.xpm",	&img_width, &img_height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
		"./images/exit.xpm", &img_width, &img_height);
	data->img_collects = mlx_xpm_file_to_image(data->mlx_ptr,
		"./images/milk.xpm", &img_width, &img_height);
	if (!data->img_exit || !data->img_collects || !data->img_player
		|| !data->img_wall)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_exit);
		mlx_destroy_image(data->mlx_ptr, data->img_collects);
		mlx_destroy_image(data->mlx_ptr, data->img_player);
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
		handle_error("Failed to load image");
	}
}

void	load_elements(t_data *data, t_game *game)
{
	int	i;
	int	j;
	
	load_images(data);
	i = -1;
	while (++i < game->row_count)
	{
		j = -1;
		while (++j < game->col_count)
		{
			if ((game->map)[i][j] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_exit, j * 32, i * 32);
			else if ((game->map)[i][j] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_player, j * 32, i * 32);
			else if ((game->map)[i][j] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_collects, j * 32, i * 32);
			else if ((game->map)[i][j] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->img_wall, j * 32, i * 32);
		}
	}
}
