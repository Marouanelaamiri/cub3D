/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:35:29 by aromani           #+#    #+#             */
/*   Updated: 2025/08/15 19:07:17 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_TILE_SIZE 11
#define PLAYER_SIZE 5.5        

uint32_t get_color(t_data *data, float tx, float ty, float half_visible)
{
    // World tile coordinates relative to player
    int map_x = (data->player_x / TILE_SIZE) - half_visible + tx;
    int map_y = (data->player_y / TILE_SIZE) - half_visible + ty;

    uint32_t color = 0x00000000;
    if (map_y >= 0 && map_y < data->recmap_height &&
        map_x >= 0 && map_x < (int)ft_strlen(data->map[map_y]))
    {
        char cell = data->map[map_y][map_x];
        if (cell == '1') color = 0x80555555;
        else if (cell == 'D')
            color = 0x000000FF; // closed door
        else color = data->f_color;
    }
    return (color);
}

void draw_minimap_tiles(t_data *data, float tx, float ty, uint32_t color)
{
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

}

void draw_player(t_data *data, float visible_tiles)
{
    int center_x = (visible_tiles * MINIMAP_TILE_SIZE) / 2;
    int center_y = (visible_tiles * MINIMAP_TILE_SIZE) / 2;

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
                0x00000FF); 
            px++;
        }
        py++;
    }
}
void draw_minimap(t_data *data)
{
    int visible_tiles = 15;
    int half_visible = visible_tiles / 2;
    uint32_t color;
    // Center of minimap in pixels
   

    // Loop over visible tiles
    int ty = 0;
    while (ty < visible_tiles)
    {
        int tx = 0;
        while (tx < visible_tiles)
        {
            color = get_color(data, tx, ty, half_visible);
            draw_minimap_tiles(data, tx, ty, color);
            tx++;
        }
        ty++;
    }
    draw_player(data, visible_tiles);
}



