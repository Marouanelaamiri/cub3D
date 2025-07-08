/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:21:26 by aromani           #+#    #+#             */
/*   Updated: 2025/07/07 23:31:43 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void set_wh_map(t_data *data)
{
    int i = 0;
    int j = 0;
    int c = 0;
    
    while (data->map[j])
    {
        i = 0;
        c = 0;
        while (data->map[j][i])
        {
            if (data->map[j][i] != ' ' && data->map[j][i] != '\t')
                c++;
            i++;
        }
        j++;
    }
    data->recmap_height = j;
    data->recmap_with = c;
}

// int put_map_2dv(t_data *data)
// {
//     set_wh_map(data);
//     printf("c = %d  || j = %d  \n", data->recmap_with, data->recmap_height);
//     data->mlx = mlx_init();
//     data->win = mlx_new_window(data->mlx, data->recmap_with * 35, data->recmap_height * 35, "Pixel Map");
//     mlx_loop(data->mlx);
//     return(0);
// }

void put_pixel(char *data, int x, int y, int color, int line_length, int bpp)
{
    int offset = y * line_length + x * (bpp / 8);
    data[offset + 0] = color & 0xFF;
    data[offset + 1] = (color >> 8) & 0xFF;
    data[offset + 2] = (color >> 16) & 0xFF;
    data[offset + 3] = 0;
}

void draw_tile(t_data *data, int tile_x, int tile_y, int color)
{
    int y;
    int x;
    
    y = 0;
    while (y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            put_pixel(data->addr,
                      tile_x * TILE_SIZE + x,
                      tile_y * TILE_SIZE + y,
                      color,
                      data->line_len,
                      data->bpp);
            x++;
        }
        y++;
    }
}

void draw_player(t_data *data, int tile_x, int tile_y, int color)
{
    int y;
    int x;

    y = 0;
    while (y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            if ((y >= 25 && y <= 35) && (x >= 25 && x <= 35))
           { 
            put_pixel(data->addr,
                      tile_x * TILE_SIZE + x,
                      tile_y * TILE_SIZE + y,
                      color,
                      data->line_len,
                      data->bpp);}
            x++;
        }
        y++;
    } 
}

int put_map_2dv(t_data *data)
{
    int y;
    int x;

    y = 0;
    set_wh_map(data); 
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx,
                data->recmap_with * TILE_SIZE,
                data->recmap_height * TILE_SIZE,
                "Pixel Map");
    data->img = mlx_new_image(data->mlx,
                data->recmap_with * TILE_SIZE,
                data->recmap_height * TILE_SIZE);
    data->addr = mlx_get_data_addr(data->img,
                &data->bpp, &data->line_len, &data->endian);
    while (y < data->recmap_height)
    {
        x = 0;
        while (x < data->recmap_with)
        {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')
                draw_player(data, x, y, GREEN);
            else if (data->map[y][x] == '1')
                draw_tile(data, x, y, RED);
            else
                draw_tile(data, x, y, BLACK);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_loop(data->mlx);
    return (0);
}
