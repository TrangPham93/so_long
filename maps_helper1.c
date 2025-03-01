/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_helper1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:07:10 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 17:51:04 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	is_valid_filename(const char *str)
{
	int		len;
	char	*file_type;

	len = ft_strlen(str);
	file_type = ft_substr(str, len - 4, 4);
	if (!file_type)
		handle_error("substr file type not succeed", NULL);
	if (ft_strcmp(file_type, ".ber") != 0)
		handle_error("Not a valid file", file_type);
	free(file_type);
}

int	not_allowed_element(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*game).row_count)
	{
		j = 0;
		while (j < (*game).col_count)
		{
			if ((game->map)[i][j] != 'P' && (game->map)[i][j] != 'E'
				&& (game->map)[i][j] != 'C' && (game->map)[i][j] != '1'
				&& (game->map)[i][j] != '0')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_path(t_game *game)
{
	char	**temp_map;
	int		is_valid;

	temp_map = duplicate_map(game);
	if (!temp_map)
		handle_error("Cannot duplicate map", NULL);
	is_valid = exit_reachable(game, temp_map, game->player.x, game->player.y);
	free_arr(temp_map, game->row_count);
	if (is_valid != 0)
		handle_error("Cannot reach exit on map", NULL);
	temp_map = duplicate_map(game);
	if (!temp_map)
		handle_error("Cannot duplicate map", NULL);
	is_valid = check_all_collectables(game, temp_map);
	free_arr(temp_map, game->row_count);
	if (is_valid != 0)
		handle_error("Cannot reach collectable on map", NULL);
	return (0);
}

char	**duplicate_map(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = malloc(sizeof(char *) * game->row_count);
	if (!temp_map)
		handle_error("Memory allocation for temporary map failed", NULL);
	i = 0;
	while (i < game->row_count)
	{
		temp_map[i] = ft_strdup((game->map)[i]);
		if (!temp_map[i])
		{
			free_arr(temp_map, i);
			handle_error("ft_strdup row failed", NULL);
		}
		i++;
	}
	return (temp_map);
}
