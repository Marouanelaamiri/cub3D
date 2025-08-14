/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:20:52 by aromani           #+#    #+#             */
/*   Updated: 2025/08/14 15:46:28 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_struct(t_data *data)
{
	data->img      = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	data->addr     = (char *)data->img->pixels;
	data->bpp      = 32;
	data->line_len = data->img->width * 4;
	data->endian   = 0;
	data->fov      = FOV;
}

void init_player(t_data *data)
{
	int	iy;
	int	ix;
	
	iy = 0;
	while (iy < data->recmap_height)
	{
		ix = 0;
		while (data->map[iy][ix])
		{
			if (ft_strchr("NSWE", data->map[iy][ix]))
			{
				data->player_x  = ix * TILE_SIZE + TILE_SIZE / 2;
				data->player_y  = iy * TILE_SIZE + TILE_SIZE / 2;
				data->ray_angle = get_angle_from_dir(data->map[iy][ix]);
			}
			ix++;
		}
		iy++;
	}
}