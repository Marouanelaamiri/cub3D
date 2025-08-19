/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:46 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/19 18:40:23 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	tile_direction(float v)
{
	if (v > 0.5f)
		return (1);
	if (v < -0.5f)
		return (-1);
	return (0);
}

void	toggle_door(t_data *data)
{
	int	py;
	int	px;
	int	tx;
	int	ty;

	py = (int)(data->player_y / TILE_SIZE);
	px = (int)(data->player_x / TILE_SIZE);
	tx = px + tile_direction(cosf(data->ray_angle));
	ty = py + tile_direction(sinf(data->ray_angle));
	if (data->map[ty][tx] == DOOR_CLOSED)
		data->map[ty][tx] = DOOR_OPEN;
	else if (data->map[ty][tx] == DOOR_OPEN)
	{
		if (py == ty && px == tx)
			return ;
		data->map[ty][tx] = DOOR_CLOSED;
	}
}
