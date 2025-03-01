/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:35 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 16:17:10 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_window(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->game->col_count * IMG_W,
			data->game->row_count * IMG_H, "so_long");
	if (!data->mlx_win)
	{
		free_arr(data->game->map, data->game->row_count);
		if (data->mlx_ptr)
			mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		handle_error("Failed to initialize a window", NULL);
	}
}

// void	load_background(t_data *data)
// {
	
// }

// void	load_images(t_data *data)
// {
	
// }
void	render_img_background(t_data *data)
{
	int		i;
	int		j;

	
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

	// load_images(data);
	i = -1;
	while (++i < data->game->row_count)
	{
		j = -1;
		while (++j < data->game->col_count)
		{
			if ((data->game->map)[i][j] == 'E')
			{
				data->game->exit.y = i;
				data->game->exit.x = j;
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

void	handle_error(char *s, char *to_free)
{
	if (to_free)
		free(to_free);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 2);
	// perror(s);
	exit(-1);
}

void	print_map(char **map, t_game *game)
{
	int	i;

	i = 0;
	if (!map)
		handle_error("there is no map to print", NULL);
	while (i < game->row_count)
	{
		printf("%s\n", map[i]);
		i++;
	}
}


void	free_arr(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// void	free_map(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->game->row_count)
// 	{
// 		free(data->game->map[i]);
// 		i++;
// 	}
// 	free(data->game->map);
// }

void	winner_print(void)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("|    🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉     |\n");
	ft_printf("|    You found all collectibles and exit.     |\n");
	ft_printf("|        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           |\n");
	ft_printf("-----------------------------------------------\n");
	exit(0);
}
