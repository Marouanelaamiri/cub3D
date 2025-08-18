/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:12:00 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 20:13:44 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
