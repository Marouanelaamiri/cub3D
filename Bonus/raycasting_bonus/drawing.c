/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:16:33 by aromani           #+#    #+#             */
/*   Updated: 2025/08/15 18:33:16 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_texters(t_data *data)
{
	if (data->hit_is_door) 
	{
        data->tex = data->door;        // <— door texture when we hit a door
        return;
    }
	if (data->hit_side == 'N') 
        data->tex = data->no;
    else if (data->hit_side == 'S') 
        data->tex = data->so;
    else if (data->hit_side == 'W') 
        data->tex = data->we;
    else                            
        data->tex = data->ea;
}

void draw_wall(t_data *data, int wall_h, int top, int y_col[2])
{
    int col;
    int y;
    uint32_t *pxs;
    float ratio;
    int tex_y;
    uint32_t color;
    
    y = y_col[0];
    col = y_col[1];
    pxs = (uint32_t *)data->tex->pixels;
    ratio = (float)(y - top) / wall_h;
    tex_y = (int)(ratio * (data->tex->height - 1));
    tex_y = fmax(0, fmin(data->tex->height - 1, tex_y));
    color =  pxs[(int)(tex_y * data->tex->width + data->tex_x)];
    put_pixel(data, col, y, color);
}

static void ft_paint(t_data *data, float dist, int col)
{
	int wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / dist); // used to be int wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / fmaxf(dist, 0.1f));
    int top = (MAP_HEIGHT - wall_h) / 2;
    int bottom = top + wall_h;
	int y = 0;
    int array[2];

	while (y < MAP_HEIGHT)
    {
        if (y < top)
            mlx_put_pixel(data->img, col, y, data->c_color);
        else if (y > top && y < bottom)
        {
            array[0] = y;
            array[1] = col;
            draw_wall(data, wall_h, top, array);
        }
        else if (y > bottom)
            mlx_put_pixel(data->img, col, y, data->f_color);
		y++;
    }
}

static void draw_column(t_data *data, int col, float dist)
{
	init_texters(data);
    float wall_x = fmodf(data->hit_wall_x, TILE_SIZE);
    if (wall_x < 0)
		wall_x += TILE_SIZE;
    data->tex_x = (int)(wall_x * data->tex->width);
    
    if (data->hit_side == 'S' || data->hit_side == 'E')
        data->tex_x = data->tex->width - data->tex_x - 1;
    data->tex_x = fmax(0, fmin(data->tex->width - 1, data->tex_x));
    ft_paint(data, dist, col);
}

static void render_3d(t_data *data)
{
    int   w     = MAP_WIDTH;
    float step  = data->fov / (float)w;
    float angle = data->ray_angle - (data->fov / 2);
	int         col   = 0;

    while (col < w)
    {
        float raw_dist = cast_ray(data, angle);
        float diff = angle - data->ray_angle;
        float corrected = raw_dist * cosf(diff);
        draw_column(data, col, corrected);
        angle += step;
        col++;
    }
}

void	redraw(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	init_struct(data);
	render_3d(data);
    draw_minimap(data);
	draw_reload_overlay(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}