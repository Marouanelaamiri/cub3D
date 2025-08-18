/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:16:33 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 18:31:13 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_texters(t_data *data)
{
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
	int wall_h;
	int top;
	int bottom;
	int y;
	int array[2];
	
	wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / dist);
	top = (MAP_HEIGHT - wall_h) / 2;
	bottom = top + wall_h;
	y = 0;
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
	float wall_x;

	init_texters(data);
	wall_x = fmodf(data->hit_wall_x, TILE_SIZE);
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
	float	step;
	float	angle;
	int		col;
	float raw_dist;
	float corrected;

	step  = data->fov / (float)MAP_WIDTH;
	angle = data->ray_angle - (data->fov / 2);
	col   = 0;
	while (col < MAP_WIDTH)
	{
		raw_dist = cast_ray(data, angle);
		corrected = raw_dist * cosf( angle - data->ray_angle);
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
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}