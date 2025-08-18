/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:20:52 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 20:13:47 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void free_textures(t_data *data)
{
	if (data->no)
	{
		mlx_delete_texture(data->no);
		data->no = NULL;
	}
    if (data->so)
	{
		mlx_delete_texture(data->so);
		data->so = NULL;
	}
    if (data->we)
	{
		mlx_delete_texture(data->we);
		data->we = NULL;
	}
    if (data->ea)
	{
		mlx_delete_texture(data->ea);
		data->ea = NULL;
	}
    if (data->img)
	{
		mlx_delete_image(data->mlx, data->img);
		data->img = NULL;
	}
}

void	free_graphics_and_textures(t_data *data)
{
    if (!data)
        return;
    free_textures(data);
}
