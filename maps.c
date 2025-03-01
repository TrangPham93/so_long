/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 17:00:06 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(const char *file_name, t_data *data)
{
	int		fd;
	char	*read_str;
	char	*row;
	char	*temp;

	is_valid_filename(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open map", NULL);
	read_str = ft_strdup("");
	if (!read_str)
		handle_error("Memory allocation failed\n", read_str);
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		temp = ft_strjoin(read_str, row);
		free(row);
		free(read_str);
		if (!temp)
			handle_error("String join failed\n", NULL);
		read_str = temp;
	}
	validate_map(read_str, data);
	// free(read_str);
	close(fd);
}

void	validate_map(char *str, t_data *data)
{
	int	row_count;
	int	i;

	row_count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			row_count++;
		i++;
	}
	data->game->row_count = row_count;
	data->game->map = ft_split(str, '\n');
	if (!data->game->map)
	{
		free(str);
		handle_error("Memory allocation failed in ft_split\n", NULL);
	}
	if (is_rectangular(data->game) || is_walled(data->game)
		|| have_three_elements(data->game) || not_allowed_element(data->game)
		|| check_path(data->game))
	{
		free_arr(data->game->map, data->game->row_count);
		// free_map(data);
		free(str);
		handle_error("This is a bad map, please use another map!", NULL);
	}
	free(str);
}

int	is_rectangular(t_game *game)
{
	int	i;
	int	len;
	int	std_len;

	i = 0;
	std_len = ft_strlen((game->map)[0]);
	while (i < (*game).row_count)
	{
		len = ft_strlen((game->map)[i]);
		if (len != std_len)
			return (-1);
		i++;
	}
	game->col_count = std_len;
	return (0);
}

int	is_walled(t_game *game)
{
	int	i;
	int	j;
	int	last_row;
	int	last_col;

	i = 0;
	j = 0;
	last_row = (*game).row_count - 1;
	last_col = (*game).col_count - 1;
	while (j <= last_col)
	{
		if ((game->map)[0][j] != '1' || (game->map)[last_row][j] != '1')
			return (-1);
		j++;
	}
	while (i <= last_row)
	{
		if ((game->map)[i][0] != '1' || (game->map)[i][last_col] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	have_three_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < (*game).row_count - 1)
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
			else if ((game->map)[i][j] == 'E')
			{
				(*game).exit_count++;
				game->exit.y = i;
				game->exit.x = j;
			}
			else if ((game->map)[i][j] == 'C')
				(*game).collectible_count++;
			j++;
		}
	}
	if ((*game).player_count != 1 || (*game).exit_count != 1
		|| (*game).collectible_count < 1)
		return (-1);
	return (0);
}

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

	// printf("enter check path\n");
	temp_map = duplicate_map(game);
	if (!temp_map)
		handle_error("Cannot duplicate map", NULL);
	is_valid = exit_reachable(game, temp_map, game->player.x, game->player.y);
	free_arr(temp_map, game->row_count);
	// free_temp_map(game, temp_map);
	if (is_valid != 0)
		handle_error("Cannot reach exit on map", NULL);
	temp_map = duplicate_map(game);
	if (!temp_map)
		handle_error("Cannot duplicate map", NULL);
	is_valid = check_all_collectables(game, temp_map);
	// printf("check all collects\n");
	// free_temp_map(game, temp_map);
	free_arr(temp_map, game->row_count); //can be double free
	if (is_valid != 0)
		handle_error("Cannot reach collectable on map", NULL);
	// printf("path ok\n");
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

// void	free_temp_map(t_game *game, char **temp_map)
// {
// 	int	i;

// 	if (temp_map != NULL)
// 	{
// 		i = 0;
// 		while (i < game->row_count)
// 		{
// 			if (temp_map[i])
// 				free(temp_map[i]);
// 			i++;
// 		}
// 		free(temp_map);
// 	}
// }

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
	// char	**new_map;

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
	// printf("finish while\n");
	// free_arr(temp_map, i);
	return (0);
}
void	reset_temp_map(t_game *game, char **temp_map)
{
	int	i;
	int	j;

	i = 0;
	// j = 0;
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
