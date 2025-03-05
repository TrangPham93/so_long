/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_helper3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:33:11 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 14:34:53 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	one_exit(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < (*game).row_count - 1)
	{
		j = 1;
		while (j < (*game).col_count - 1)
		{
			if ((game->map)[i][j] == 'E')
				(*game).exit_count++;
			j++;
		}
		i++;
	}
	if ((*game).exit_count != 1)
	{
		handle_error("None or more than 1 exit", NULL);
		return (-1);
	}
	return (0);
}

int	collectible_exist(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < (*game).row_count - 1)
	{
		j = 1;
		while (j < (*game).col_count - 1)
		{
			if ((game->map)[i][j] == 'C')
				(*game).collectible_count++;
			j++;
		}
		i++;
	}
	if ((*game).collectible_count < 1)
	{
		handle_error("No collectibles on map", NULL);
		return (-1);
	}
	return (0);
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
