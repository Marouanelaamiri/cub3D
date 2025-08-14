/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:35:29 by aromani           #+#    #+#             */
/*   Updated: 2025/08/14 23:18:10 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_TILE_SIZE 12   // wall/floor pixel size
#define PLAYER_SIZE 6         // player square size

void draw_minimap(t_data *data)
{
    int visible_tiles = 15;
    int half_visible = visible_tiles / 2;

    // Player position in world
    float player_world_x = data->player_x;
    float player_world_y = data->player_y;

    // Center of minimap in pixels
    int center_x = (visible_tiles * MINIMAP_TILE_SIZE) / 2;
    int center_y = (visible_tiles * MINIMAP_TILE_SIZE) / 2;

    // Loop over visible tiles
    int ty = 0;
    while (ty < visible_tiles)
    {
        int tx = 0;
        while (tx < visible_tiles)
        {
            // World tile coordinates relative to player
            int map_x = (player_world_x / TILE_SIZE) - half_visible + tx;
            int map_y = (player_world_y / TILE_SIZE) - half_visible + ty;

            uint32_t color = 0x000000FF;
            if (map_y >= 0 && map_y < data->recmap_height &&
                map_x >= 0 && map_x < (int)ft_strlen(data->map[map_y]))
            {
                char cell = data->map[map_y][map_x];
                if (cell == '1') color = 0xFFFFFFFF;
                else color = 0x777777FF;
            }

            // Draw tile
            int draw_x = tx * MINIMAP_TILE_SIZE;
            int draw_y = ty * MINIMAP_TILE_SIZE;

            int dy = 0;
            while (dy < MINIMAP_TILE_SIZE)
            {
                int dx = 0;
                while (dx < MINIMAP_TILE_SIZE)
                {
                    mlx_put_pixel(data->img, draw_x + dx, draw_y + dy, color);
                    dx++;
                }
                dy++;
            }

            tx++;
        }
        ty++;
    }

    // Draw player (always in center)
    int py = 0;
    while (py < PLAYER_SIZE)
    {
        int px = 0;
        while (px < PLAYER_SIZE)
        {
            mlx_put_pixel(data->img,
                center_x - PLAYER_SIZE / 2 + px,
                center_y - PLAYER_SIZE / 2 + py,
                0xFF0000FF);
            px++;
        }
        py++;
    }
}



