/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/03/02 11:30:25 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(const char *file_name, t_data *data)
{
	int		fd;
	char	*read_str;

	is_valid_filename(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		handle_error("Failed to open map", NULL);
	read_str = read_and_join_line(fd);
	validate_map(read_str, data);
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
	return (read_str);
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
		handle_error("Memory allocation failed in ft_split\n", str);
	if (is_rectangular(data->game) || is_walled(data->game)
		|| one_player_and_exit(data->game) || collectible_exist(data->game)
		|| not_allowed_element(data->game) || check_path(data->game))
	{
		free_arr(data->game->map, data->game->row_count);
		handle_error("This is a bad map, please use another map!", str);
	}
	free(str);
}

int	one_player_and_exit(t_game *game)
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
				(*game).exit_count++;
			j++;
		}
	}
	if ((*game).player_count != 1 || (*game).exit_count != 1)
		return (-1);
	return (0);
}

int	collectible_exist(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < (*game).row_count - 1)
	{
		j = 1;
		while (j < (*game).col_count - 1)
		{
			if ((game->map)[i][j] == 'C')
				(*game).collectible_count++;
			j++;
		}
	}
	if ((*game).collectible_count < 1)
		return (-1);
	return (0);
}
