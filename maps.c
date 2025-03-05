/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 13:24:14 by trpham           ###   ########.fr       */
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
	// ft_printf("%s\n", read_str);
	if (ft_strcmp(read_str, "") == 0)
	{
		close(fd);
		handle_error("Map is empty", read_str);
		exit(-1);
	}
	if (validate_map(read_str, data) == -1)
	{
		// ft_printf("%s\n", read_str);
		close(fd);
		

		// if (read_str == NULL)
		// 	ft_printf("free read_str");
		// handle_error("Invalid map", NULL);
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
	{
		handle_error("Memory allocation failed", read_str);
		close(fd);
		exit(-1);
	}
	row = get_next_line(fd);
	if (!row)
	{
		handle_error("Not a valid file", read_str);
		close(fd);
		exit(-1);
	}
	while (row)
	{
		temp = ft_strjoin(read_str, row);
		ft_free(row);
		ft_free(read_str);
		if (!temp)
		{
			handle_error("String join failed", NULL);
			close(fd);
			exit(-1);
		}
		read_str = temp;
		row = get_next_line(fd);
	}
	free(row);
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
		if (str[i] == '\n' && str[i - 1] == '\n')
		{
			handle_error("Invalid map", str);
			// ft_free(str);
			return (-1);
		}
		if (str[i] == '\n' && str[i - 1] != '\n')
			row_count++;	
		i++;
	}
	data->game->row_count = row_count;
	data->game->map = ft_split(str, '\n');
	if (!data->game->map)
	{
		handle_error("Split failed", str);
		return (-1);
	}
	ft_free(str);
	if (is_rectangular(data->game) || is_walled(data->game)
		|| one_player(data->game) || one_exit(data->game)
		|| collectible_exist(data->game) || not_allowed_element(data->game)
		|| check_path(data->game))
	{
		free_arr(data->game->map, data->game->row_count);
		data->game->map = NULL;
		// ft_free(str);
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

int	one_exit(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	// ft_printf("%d\n", (*game).exit_count);

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
	// ft_printf("%d\n", (*game).exit_count);
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
