/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:21 by trpham            #+#    #+#             */
/*   Updated: 2025/02/28 21:46:00 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(char *s)
{
	ft_printf("Error\n");
	perror(s);
	exit(-1);
}

void	print_map(char **map, t_game *game)
{
	int	i;

	i = 0;
	if (!map)
		handle_error("there is no map to print");
	while (i < game->row_count)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	free_mlx(t_data *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr); // is this necessary?
	}
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->game->row_count)
	{
		free(data->game->map[i]);
		i++;
	}
	free(data->game->map);
}

void	winner_print(void)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("|    🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉     |\n");
	ft_printf("|    You found all collectibles and exit.     |\n");
	ft_printf("|        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           |\n");
	ft_printf("-----------------------------------------------\n");
	exit(0);
}
