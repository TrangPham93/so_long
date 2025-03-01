/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:43:22 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 17:50:41 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	exit_reachable(t_game *game, char **temp_map, int x, int y)
{
	if (x < 1 || x >= game->col_count - 1 || y < 1 || y >= game->row_count - 1
		|| temp_map[y][x] == '1' || temp_map[y][x] == 'V')
		return (-1);
	if (temp_map[y][x] == 'E')
		return (0);
	temp_map[y][x] = 'V';
	if (exit_reachable(game, temp_map, x + 1, y) == 0
		|| exit_reachable(game, temp_map, x - 1, y) == 0
		|| exit_reachable(game, temp_map, x, y + 1) == 0
		|| exit_reachable(game, temp_map, x, y - 1) == 0)
		return (0);
	return (-1);
}

int	collectables_reachable(t_game *game, char **temp_map, int x, int y)
{
	if (x < 1 || x >= game->col_count - 1 || y < 1 || y >= game->row_count - 1
		|| temp_map[y][x] == '1' || temp_map[y][x] == 'V')
		return (-1);
	if (temp_map[y][x] == 'P')
		return (0);
	temp_map[y][x] = 'V';
	if (collectables_reachable(game, temp_map, x + 1, y) == 0
		|| collectables_reachable(game, temp_map, x - 1, y) == 0
		|| collectables_reachable(game, temp_map, x, y + 1) == 0
		|| collectables_reachable(game, temp_map, x, y - 1) == 0)
		return (0);
	return (-1);
}

int	check_all_collectables(t_game *game, char **temp_map)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->row_count)
	{
		j = 0;
		while (j < game->col_count)
		{
			if (temp_map[i][j] == 'C')
			{
				if (collectables_reachable(game, temp_map, j, i) != 0)
				{
					return (-1);
				}
				reset_temp_map(game, temp_map);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	reset_temp_map(t_game *game, char **temp_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->row_count)
	{
		j = 0;
		while (j < game->col_count)
		{
			if (temp_map[i][j] == 'V')
				temp_map[i][j] = '0';
			j++;
		}
		i++;
	}
}