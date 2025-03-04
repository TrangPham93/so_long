/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/03/04 18:13:43 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/so_long.h"

void	read_map(const char *file_name, t_data *data)
{
	int		fd;
	char	*read_str;

	is_valid_filename(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open map", NULL);
	read_str = read_and_join_line(fd);
	if (ft_strcmp(read_str, "") == 0)
	{
		close(fd);
		handle_error("Map is empty", read_str);
	}
	if (validate_map(read_str, data) == -1)
	{
		close(fd);
		handle_error("Invalid map", read_str);
	}
	close(fd);
}

char	*read_and_join_line(int fd)
{
	char	*read_str;
	char	*row;
	char	*temp;

	read_str = ft_strdup("");
	if (!read_str)
		handle_error("Memory allocation failed\n", read_str);
	row = get_next_line(fd);
	if (!row)
	{
		free(read_str);
		free(row);
		close(fd);
		handle_error("Not a file", NULL);
	}
	while (row)
	{
		temp = ft_strjoin(read_str, row);
		free(row);
		free(read_str);
		if (!temp)
			handle_error("String join failed", NULL);
		read_str = temp;
		row = get_next_line(fd);
	}
	// free(row);
	return (read_str);
}

int	validate_map(char *str, t_data *data)
{
	int	row_count;
	int	i;

	row_count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i - 1] != '\n')
			return (-1);
		i++;
	}
	data->game->row_count = row_count;
	data->game->map = ft_split(str, '\n');
	if (!data->game->map)
		return (-1);
	if (is_rectangular(data->game) || is_walled(data->game)
		|| one_player_and_exit(data->game) || collectible_exist(data->game)
		|| not_allowed_element(data->game) || check_path(data->game))
	{
		free_arr(data->game->map, data->game->row_count);
		return (-1);
	}
	return (0);
}

int	one_player_and_exit(t_game *game)
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
			else if ((game->map)[i][j] == 'E')
				(*game).exit_count++;
			j++;
		}
		i++;
	}
	if ((*game).player_count != 1 || (*game).exit_count != 1)
		return (-1);
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
		return (-1);
	return (0);
}
