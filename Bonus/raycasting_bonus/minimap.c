/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:35:29 by aromani           #+#    #+#             */
/*   Updated: 2025/08/20 19:47:04 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"      

uint32_t	get_color(t_data *data, float tx, float ty, float map_radius)
{
	int			map_x;
	int			map_y;
	uint32_t	color;

	map_x = (data->player_x / TILE_SIZE) - map_radius + tx;
	map_y = (data->player_y / TILE_SIZE) - map_radius + ty;
	color = 0x00000FF;
	if (map_y >= 0 && map_y < data->recmap_height && map_x \
		>= 0 && map_x < (int)ft_strlen(data->map[map_y]))
	{
		if (data->map[map_y][map_x] == '1')
			color = 0x80808080;
		else if (data->map[map_y][map_x] == 'D')
			color = 0x000000FF;
		else
			color = 0xEE4B2BFF;
	}
	return (color);
}

void	draw_minimap_tiles(t_data *data, float tx, float ty, uint32_t color)
{
	int	draw_x;
	int	draw_y;
	int	dy;
	int	dx;

	draw_x = tx * MINIMAP_TILE_SIZE;
	draw_y = ty * MINIMAP_TILE_SIZE;
	dy = 0;
	while (dy < MINIMAP_TILE_SIZE)
	{
		dx = 0;
		while (dx < MINIMAP_TILE_SIZE)
		{
			mlx_put_pixel(data->img, draw_x + dx, draw_y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_player(t_data *data, float tiles)
{
	int	center_x;
	int	center_y;
	int	py;
	int	px;

	center_x = (tiles * MINIMAP_TILE_SIZE) / 2;
	center_y = (tiles * MINIMAP_TILE_SIZE) / 2;
	py = 0;
	while (py < PLAYER_SIZE)
	{
		px = 0;
		while (px < PLAYER_SIZE)
		{
			mlx_put_pixel(data->img,
				center_x - PLAYER_SIZE / 2 + px,
				center_y - PLAYER_SIZE / 2 + py,
				0x00000FF);
			px++;
		}
		py++;
	}
}

void	draw_minimap(t_data *data)
{
	int			tiles;
	int			map_radius;
	uint32_t	color;
	int			ty;
	int			tx;

	tiles = 15;
	map_radius = tiles / 2;
	ty = 0;
	while (ty < tiles)
	{
		tx = 0;
		while (tx < tiles)
		{
			color = get_color(data, tx, ty, map_radius);
			draw_minimap_tiles(data, tx, ty, color);
			tx++;
		}
		ty++;
	}
	draw_player(data, tiles);
}
