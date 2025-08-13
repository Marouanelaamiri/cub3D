/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:46 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/13 21:28:01 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int sgnf(float v)
{
    if (v > 0.5f) return 1;
    if (v < -0.5f) return -1;
    return 0;
}

/* Toggle the tile in front of the player. If opening, record door state for auto-close. */
void toggle_door(t_data *data)
{
    int px = (int)(data->player_x); /* player tile coord (your movement code uses tiles) */
    int py = (int)(data->player_y);
    int tx = px + sgnf(cosf(data->ray_angle));
    int ty = py + sgnf(sinf(data->ray_angle));

    if (ty < 0 || ty >= data->recmap_height)
        return ;
    if (tx < 0 || tx >= (int)ft_strlen(data->map[ty]))
        return ;

    if (data->map[ty][tx] == DOOR_CLOSED)
    {
        data->map[ty][tx] = DOOR_OPEN;   /* open it */
        data->door_open = 1;
        data->door_x = tx;
        data->door_y = ty;
        data->door_nx = sgnf(cosf(data->ray_angle));
        data->door_ny = sgnf(sinf(data->ray_angle));
        return ;
    }
    if (data->map[ty][tx] == DOOR_OPEN)
    {
        /* if the player is standing in that tile, do not close it */
        if ((int)(data->player_x) == tx && (int)(data->player_y) == ty)
            return ;
        data->map[ty][tx] = DOOR_CLOSED;
        data->door_open = 0;
    }
}
int update_auto_close_door(t_data *data)
{
    float relx;
    float rely;
    float dot;

    if (!data->door_open)
        return (0);

    /* vector from door tile -> player position (in tiles, float) */
    relx = data->player_x - (float)data->door_x;
    rely = data->player_y - (float)data->door_y;

    /* dot with the normal that was recorded when opening */
    dot = relx * (float)data->door_nx + rely * (float)data->door_ny;

    /* If player is now on the other side (dot > 0.5), auto-close the door.
       Threshold 0.5 keeps it from closing while player is still crossing. */
    if (dot > 0.5f)
    {
        /* but ensure player is not standing on the door tile itself */
        if ((int)data->player_x == data->door_x && (int)data->player_y == data->door_y)
            return (0);
        /* close it */
        if (data->map[data->door_y][data->door_x] == DOOR_OPEN)
            data->map[data->door_y][data->door_x] = DOOR_CLOSED;
        data->door_open = 0;
        return (1);
    }
    return (0);
}
