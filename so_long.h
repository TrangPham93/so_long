/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:39:11 by trpham            #+#    #+#             */
/*   Updated: 2025/02/18 15:31:28 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h> // for perror()
// #include <keysym.h>

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;

}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
}	t_img;



#endif