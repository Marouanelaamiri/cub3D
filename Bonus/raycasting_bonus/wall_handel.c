/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_handel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:08:54 by aromani           #+#    #+#             */
/*   Updated: 2025/08/19 21:29:37 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	corner_check(t_data *data, float corners[4][2], int i)
{
	int		mx;
	int		my;
	char	tile;

	mx = (int)(corners[i][0] / TILE_SIZE);
	my = (int)(corners[i][1] / TILE_SIZE);
	if (my < 0 || my >= data->recmap_height
		|| mx < 0 || mx >= (int)ft_strlen(data->map[my]))
		return (1);
	tile = data->map[my][mx];
	if (tile == '1' || tile == DOOR_CLOSED)
		return (1);
	return (0);
}

void	init_corners(float corners[4][2], float px, float py)
{
	float	r;

	r = COLLIDE_PAD * TILE_SIZE;
	corners[0][0] = px - r;
	corners[0][1] = py - r;
	corners[1][0] = px + r;
	corners[1][1] = py - r;
	corners[2][0] = px - r;
	corners[2][1] = py + r;
	corners[3][0] = px + r;
	corners[3][1] = py + r;
}

int	corner_handel(t_data *data, float new_px, float new_py)
{
	float	px;
	float	py;
	int		i;
	float	corners[4][2];

	px = new_px;
	py = new_py ;
	i = 0;
	init_corners(corners, px, py);
	while (i < 4)
	{
		if (corner_check(data, corners, i))
			return (1);
		i++;
	}
	return (0);
}

int	is_colliding(t_data *data, float new_px, float new_py)
{
	int		tile_x;
	int		tile_y;
	char	tile;

	tile_x = (int)(new_px / TILE_SIZE);
	tile_y = (int)(new_py / TILE_SIZE);
	if (tile_y >= 0 && tile_y < data->recmap_height
		&& tile_x >= 0 && tile_x < (int)ft_strlen(data->map[tile_y]))
	{
		tile = data->map[tile_y][tile_x];
		if (tile == '1' || tile == DOOR_CLOSED)
			return (1);
	}
	if (corner_handel(data, new_px, new_py))
		return (1);
	return (0);
}
