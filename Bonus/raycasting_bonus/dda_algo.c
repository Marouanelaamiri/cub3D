/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:48:40 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 20:13:24 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void vertecal_clacule(t_data *data)
{
	float adjacent;
	
	adjacent = 0.0;
	if (data->algo->step_x < 0)
	{
		adjacent = (data->algo->px - data->algo->map_x * TILE_SIZE);
		data->algo->side_dist_x = adjacent * data->algo->delta_x;
	}
	else
	{
		adjacent = ((data->algo->map_x + 1) * TILE_SIZE - data->algo->px);
		data->algo->side_dist_x = adjacent * data->algo->delta_x;
	}
}

void horizental_calcul(t_data *data)
{
	float adjacent;
	
	adjacent = 0.0;
	if (data->algo->step_y < 0)
	{	
		adjacent = (data->algo->py - data->algo->map_y * TILE_SIZE);
		data->algo->side_dist_y = adjacent * data->algo->delta_y;
	}
	else
	{	
		adjacent = ((data->algo->map_y + 1) * TILE_SIZE - data->algo->py);
		data->algo->side_dist_y = adjacent * data->algo->delta_y;
	}

}

static void init_algo(t_data *data, float angle)
{
	data->algo->px = data->player_x;
	data->algo->py = data->player_y;
	data->algo->dir_x = cosf(angle);
	data->algo->dir_y = sinf(angle);
	data->algo->map_x = (int)(data->algo->px / TILE_SIZE);
	data->algo->map_y = (int)(data->algo->py / TILE_SIZE);
	data->algo->delta_x = fabsf(1 / data->algo->dir_x);
	data->algo->delta_y = fabsf(1 / data->algo->dir_y);
	if (data->algo->dir_x < 0)
		data->algo->step_x = -1;
	else
		data->algo->step_x = 1;
	if (data->algo->dir_y < 0)
		data->algo->step_y = -1;
	else
		data->algo->step_y = 1;
	vertecal_clacule(data);
	horizental_calcul(data);
}

int	door_check(t_data *data)
{
	int		hit;
	char	cell;
		
	hit = 0;
	cell = data->map[data->algo->map_y][data->algo->map_x];
	if (cell == '1' || cell == DOOR_CLOSED)
	{
		data->hit_is_door = (cell == DOOR_CLOSED);
		hit = 1;
	}
	return (hit);
}

static void send_ray(t_data *data)
{
    int hit = 0;

    while (!hit)
    {
        if (data->algo->side_dist_x < data->algo->side_dist_y)
        {
            data->algo->side_dist_x += data->algo->delta_x * TILE_SIZE;
            data->algo->map_x += data->algo->step_x;
            data->algo->side = 0;
        }
        else
        {
            data->algo->side_dist_y += data->algo->delta_y * TILE_SIZE;
            data->algo->map_y += data->algo->step_y;
            data->algo->side = 1;
        }

        if (data->algo->map_y < 0 || data->algo->map_y >= data->recmap_height
         || data->algo->map_x < 0 || data->algo->map_x >= (int)ft_strlen(data->map[data->algo->map_y]))
            hit = 1;
        else
			hit = door_check(data);
    }
}

static void texters_count(t_data *data, float hit_dist)
{
	float wall_x;
	float wall_y;

	wall_x	= 0.0;
	wall_y	= 0.0;
	if (data->algo->side == 0)
	{
		if (data->algo->step_x > 0)
    		data->hit_side = 'E';
		else
   			data->hit_side = 'W';
		wall_y = data->algo->py + hit_dist * data->algo->dir_y;
		data->hit_wall_x = fmodf(wall_y, TILE_SIZE) / TILE_SIZE;
	}
	else
	{
		if (data->algo->step_y > 0) 
			data->hit_side = 'S'; 
		else 
			data->hit_side = 'N';
		wall_x = data->algo->px + hit_dist * data->algo->dir_x;
		data->hit_wall_x = fmodf(wall_x, TILE_SIZE) / TILE_SIZE;
	}
}

float	cast_ray(t_data *data, float angle)
{
	float hit_dist;
	data->hit_is_door = 0;
	ft_memset(data->algo,0,sizeof(t_algo));
	init_algo(data, angle);
	send_ray(data);
	if (data->algo->side == 0)
		hit_dist = data->algo->side_dist_x - data->algo->delta_x * TILE_SIZE;
	else
		hit_dist = data->algo->side_dist_y - data->algo->delta_y * TILE_SIZE;
	texters_count(data, hit_dist);
	return (hit_dist);
}