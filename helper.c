/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:45:39 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 13:57:01 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	winner_print(void)
{
	ft_putstr_fd("-----------------------------------------------\n", 1);
	ft_putstr_fd("|    🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉     |\n", 1);
	ft_putstr_fd("|    You found all collectibles and exit.     |\n", 1);
	ft_putstr_fd("|        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           |\n", 1);
	ft_putstr_fd("-----------------------------------------------\n", 1);
}

void	handle_error(char *s, char *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

void	free_arr(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}

void	ft_free(char *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	close_file_and_exit(int fd, char *str)
{
	handle_error("Read map failed", str);
	close(fd);
	exit(-1);
}
