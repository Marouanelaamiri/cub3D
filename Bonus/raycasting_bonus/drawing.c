/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:16:33 by aromani           #+#    #+#             */
/*   Updated: 2025/08/14 00:12:45 by malaamir         ###   ########.fr       */
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

static void ft_paint(t_data *data, uint32_t *pxs, float dist, int col)
{
	int wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / dist); // used to be int wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / fmaxf(dist, 0.1f));
    int top = (MAP_HEIGHT - wall_h) / 2;
    int bottom = top + wall_h;
	int y = 0;

	while (y < MAP_HEIGHT)
    {
        if (y < top)
            mlx_put_pixel(data->img, col, y, data->c_color);
        else if (y > top && y < bottom)
        {
            float ratio = (float)(y - top) / wall_h;
            int tex_y = (int)(ratio * (data->tex->height - 1));
            tex_y = fmax(0, fmin(data->tex->height - 1, tex_y));
            //int tex_index = tex_y * data->tex->width + data->tex_x;
            uint32_t color =  pxs[(int)(tex_y * data->tex->width + data->tex_x)];
            put_pixel(data, col, y, color);
        }
        else if (y > bottom)
            mlx_put_pixel(data->img, col, y, data->f_color);
		y++;
    }
}

static void draw_column(t_data *data, int col, float dist)
{
	init_texters(data);
    uint32_t *pxs = (uint32_t *)data->tex->pixels;
	
    float wall_x = fmodf(data->hit_wall_x, TILE_SIZE);
    if (wall_x < 0)
		wall_x += TILE_SIZE;
    data->tex_x = (int)(wall_x * data->tex->width);
    
    if (data->hit_side == 'S' || data->hit_side == 'E')
        data->tex_x = data->tex->width - data->tex_x - 1;
    data->tex_x = fmax(0, fmin(data->tex->width - 1, data->tex_x));
    ft_paint(data, pxs, dist, col);
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
        const float min_px = RENDER_PAD * TILE_SIZE;
        if (raw_dist < min_px)
            raw_dist = min_px;
        float diff = angle - data->ray_angle;
        float corrected = raw_dist * cosf(diff);
        if (corrected < min_px)
            corrected = min_px;
        draw_column(data, col, corrected);
        angle += step;
        ++col;
    }
}

void	redraw(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	init_struct(data);
	render_3d(data);
	draw_reload_overlay_simple(data); /* overlay frame */
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}