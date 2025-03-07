/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/03/07 15:00:29 by trpham           ###   ########.fr       */
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
	{
		handle_error("Failed to open map", NULL);
		exit(-1);
	}
	read_str = read_and_join_line(fd);
	if (validate_map(read_str, data) == -1)
	{
		close(fd);
		exit(-1);
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
		close_file_and_exit(fd, read_str);
	row = get_next_line(fd);
	if (!row)
		close_file_and_exit(fd, read_str);
	while (row)
	{
		temp = ft_strjoin(read_str, row);
		ft_free(row);
		ft_free(read_str);
		if (!temp)
			close_file_and_exit(fd, NULL);
		read_str = temp;
		row = get_next_line(fd);
	}
	ft_free(row);
	return (read_str);
}

int	validate_map(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			handle_error("Invalid map", str);
			return (-1);
		}
		if (str[i] == '\n' && str[i + 1] != '\n')
			data->game->row_count++;
		i++;
	}
	data->game->row_count++;
	data->game->map = ft_split(str, '\n');
	if (!data->game->map)
	{
		handle_error("Split failed", str);
		return (-1);
	}
	ft_free(str);
	if (check_map_condition(data) == -1)
		return (-1);
	return (0);
}

int	check_map_condition(t_data *data)
{
	if (is_rectangular(data->game) || is_walled(data->game)
		|| one_player(data->game) || one_exit(data->game)
		|| collectible_exist(data->game) || not_allowed_element(data->game)
		|| check_path_to_exit(data->game)
		|| check_path_to_collectible(data->game))
	{
		free_arr(data->game->map, data->game->row_count);
		data->game->map = NULL;
		return (-1);
	}
	return (0);
}
