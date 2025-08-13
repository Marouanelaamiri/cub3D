/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:46 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/14 00:14:15 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int sgnf(float v)
{
    if (v > 0.5f)
		return 1;
    if (v < -0.5f)
		return -1;
    return 0;
}

void toggle_door(t_data *data)
{
    int px = (int)data->player_x;
    int py = (int)data->player_y;
    int tx = px + sgnf(cosf(data->ray_angle));
    int ty = py + sgnf(sinf(data->ray_angle));

    if (ty < 0 || ty >= data->recmap_height || tx < 0 || tx >= (int)ft_strlen(data->map[ty]))
        return;

    if (data->map[ty][tx] == DOOR_CLOSED)
        data->map[ty][tx] = DOOR_OPEN;
    else if (data->map[ty][tx] == DOOR_OPEN)
        data->map[ty][tx] = DOOR_CLOSED;
}
