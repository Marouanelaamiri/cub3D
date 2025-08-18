/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:54:12 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 21:54:41 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	slide_check(t_data *data, float corners[4][2], int i)
{
	int	mx;
	int	my;

	mx = (int)(corners[i][0] / TILE_SIZE);
	my = (int)(corners[i][1] / TILE_SIZE);
	if (my < 0 || my >= data->recmap_height
		|| mx < 0 || mx >= (int)ft_strlen(data->map[my])
		|| data->map[my][mx] == '1')
		return (1);
	return (0);
}


int	slide_handel(t_data *data, float new_px, float new_py)
{
	float	px;
	float	py;
	float	r;
	int		i;

	px = new_px;
	py = new_py ;
	r = COLLIDE_PAD * TILE_SIZE;
	i = 0;
	float corners[4][2] = {
		{ px - r, py - r },
		{ px + r, py - r },
		{ px - r, py + r },
		{ px + r, py + r }
	};
	while (i < 4)
	{
		if (slide_check(data, corners, i))
			return (1);
		i++;
	}
	return (0);
}

int	is_colliding(t_data *data, float new_px, float new_py)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)(new_px / TILE_SIZE);
	tile_y = (int)(new_py / TILE_SIZE);
	if (tile_y >= 0 && tile_y < data->recmap_height
		&& tile_x >= 0 && tile_x < (int)ft_strlen(data->map[tile_y])
		&& data->map[tile_y][tile_x] == '1')
		return (1);
	if (slide_handel(data, new_px, new_py))
		return (1);
	return (0);
}
