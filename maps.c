/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 14:16:10 by trpham           ###   ########.fr       */
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
		free_arr(data->game->map, data->game->row_count);
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
