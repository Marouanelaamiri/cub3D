/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/07/31 20:54:53 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <libc.h>

void put_pixel(t_data *d, int x, int y, int color)
{
    char *pixels = (char *)d->img->pixels;
    if (x < 0 || y < 0 || x >= (int)d->img->width || y >= (int)d->img->height)
        return;
    int off = y * d->line_len + x * (d->bpp / 8);
    pixels[off + 0] = color & 0xFF;
    pixels[off + 1] = (color >> 8) & 0xFF;
    pixels[off + 2] = (color >> 16) & 0xFF;
    pixels[off + 3] = (color >> 24) & 0xFF;
}

void draw_tile(t_data *d, int tx, int ty, int color)
{
    int yy = 0;
    while (yy < TILE_SIZE)
    {
        int xx = 0;
        while (xx < TILE_SIZE)
        {
            put_pixel(d, tx * TILE_SIZE + xx, ty * TILE_SIZE + yy, color);
            xx++;
        }
        yy++;
    }
}
void draw_player (t_data *d, int tx, int ty, int color)
{
    int yy = 0;
    while (yy < TILE_SIZE)
    {
        int xx = 0;
        while (xx < TILE_SIZE)
        {
            if ((xx >= 20 && xx <= 40) && (yy >= 20 && yy <= 40))
                put_pixel(d,tx * TILE_SIZE + xx, ty * TILE_SIZE + yy, color);
            xx++;
        }
        yy++;
    }
    
}


#include <math.h>

void draw_line(t_data *d, int color)
{
    // Start position (center of player tile)
    float x0 = d->player_x;
    float y0 = d->player_y;

    // Direction vector (based on angle)
    float dx = cos(d->player_angle);
    float dy = sin(d->player_angle);

    // End point 50 pixels in the direction of the angle
    float x1 = x0 + dx * 50;
    float y1 = y0 + dy * 50;

    // Bresenham's line algorithm
    int x = (int)x0;
    int y = (int)y0;
    int end_x = (int)x1;
    int end_y = (int)y1;

    int dx_i = abs(end_x - x);
    int dy_i = -abs(end_y - y);
    int sx = x < end_x ? 1 : -1;
    int sy = y < end_y ? 1 : -1;
    int err = dx_i + dy_i;
    int e2;

    while (1)
    {
        put_pixel(d, x, y, color);
        if (x == end_x && y == end_y)
            break;
        e2 = 2 * err;
        if (e2 >= dy_i) { err += dy_i; x += sx; }
        if (e2 <= dx_i) { err += dx_i; y += sy; }
    }
}


void draw_map2d(t_data *d)
{
    char **map = d->map;
    d->line_len = d->img->width * 4;
    d->bpp = 32;
    int y = 0;


    while (map[y])
    {
        int row_len = strlen(map[y]);
        int x = 0;
        while (x < row_len)
        {
            int color = (map[yå][x] == '1') ? COLOR_RED : 0xFFFFFFFF;
            draw_tile(d, x, y, color);
            x++;
        }
        y++;
    }
    int tile_x = (int)(d->player_x / TILE_SIZE);
    int tile_y = (int)(d->player_y / TILE_SIZE);

    draw_player(d, tile_x, tile_y, COLOR_RED);
    draw_line(d, COLOR_RED);
}


int main_raycasting(t_data *data)
{
    data->mlx = mlx_init(MAP_WITH, MAP_HIGHT, "CUB3D", 0);
    if (!data->mlx)
        return (0);
    data->img = mlx_new_image(data->mlx, MAP_WITH, MAP_HIGHT);
    if (!data->img)
        return (0);
    draw_map2d(data);
    mlx_image_to_window(data->mlx, data->img, 0,0);
    mlx_loop(data->mlx);
    return (1);
}