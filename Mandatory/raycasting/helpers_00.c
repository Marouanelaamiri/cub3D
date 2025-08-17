/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:12:00 by aromani           #+#    #+#             */
/*   Updated: 2025/08/17 19:08:30 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float get_angle_from_dir(char dir) 
{
	if (dir == 'S') 
		return (M_PI / 2);
	if (dir == 'N') 
		return (- M_PI / 2);
	if (dir == 'E') 
		return (0);
	if (dir == 'W') 
		return (M_PI);
	return (0);
}

void set_char(t_data *data, char c) 
{
	data->player_char = c;
}

// void set_fov(t_data *data, float fov) 
// {
// 	data->fov = fov;
// }

void set_wh_map(t_data *data) 
{
	int y = 0;
	int max_width = 0;
	while (data->map[y]) 
	{
		int x = 0;
		int width = 0;
		while (data->map[y][x]) 
		{
			if (data->map[y][x] != ' ' && data->map[y][x] != '\t')
				width++;
			x++;
		}
		if (width > max_width)
			max_width = width;
		y++;
	}
	data->recmap_height = y;
	data->recmap_with = max_width;
}

void	put_pixel(t_data *d, int x, int y, uint32_t color)
{
	int	offset;
	char *data;

	data = (char *)d->addr;
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
		return ;
	offset = y * d->line_len + x * (d->bpp / 8);
	data[offset + 0] = color & 0xFF;
	data[offset + 1] = (color >> 8) & 0xFF;
	data[offset + 2] = (color >> 16) & 0xFF;
	data[offset + 3] = (color >> 24) & 0xFF;
}

void	free_graphics_and_textures(t_data *data)
{
    if (!data)
        return;
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

