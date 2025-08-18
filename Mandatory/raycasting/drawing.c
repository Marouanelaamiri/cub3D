/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:16:33 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 20:06:10 by malaamir         ###   ########.fr       */
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

void draw_wall(t_data *data, int wall_height, int wall_top, int screen_pos[2])
{
	int screen_x;
	int screen_y;
	uint32_t *texture_pixels;
	float tex_ratio;
	int tex_y;
	uint32_t pixel_color;
	
	screen_y = screen_pos[0];
	screen_x = screen_pos[1];
	texture_pixels = (uint32_t *)data->tex->pixels;
	tex_ratio = (float)(screen_y - wall_top) / wall_height;
	tex_y = (int)(tex_ratio * (data->tex->height - 1));
	tex_y = fmax(0, fmin(data->tex->height - 1, tex_y));
	pixel_color = texture_pixels[(int)(tex_y * data->tex->width + data->tex_x)];
	put_pixel(data, screen_x, screen_y, pixel_color);
}


static void ft_paint(t_data *data, float distance, int screen_x)
{
	int wall_height;
	int wall_top;
	int wall_bottom;
	int screen_y;
	int screen_info[2];
	
	wall_height = (int)((TILE_SIZE * MAP_HEIGHT) / distance);
	wall_top = (MAP_HEIGHT - wall_height) / 2;
	wall_bottom = wall_top + wall_height;
	screen_y = 0;
	while (screen_y < MAP_HEIGHT)
	{
		if (screen_y < wall_top)
			mlx_put_pixel(data->img, screen_x, screen_y, data->c_color);
		else if (screen_y > wall_top && screen_y < wall_bottom)
		{
			screen_info[0] = screen_y;
			screen_info[1] = screen_x;
			draw_wall(data, wall_height, wall_top, screen_info);
		}
		else if (screen_y > wall_bottom)
			mlx_put_pixel(data->img, screen_x, screen_y, data->f_color);
		screen_y++;
	}
}

static void draw_column(t_data *data, int screen_x, float distance)
{
	float wall_hit_pos;

	init_texters(data);
	wall_hit_pos = fmodf(data->hit_wall_x, TILE_SIZE);
	if (wall_hit_pos < 0)
		wall_hit_pos += TILE_SIZE;
	data->tex_x = (int)(wall_hit_pos * data->tex->width);
	if (data->hit_side == 'S' || data->hit_side == 'E')
		data->tex_x = data->tex->width - data->tex_x - 1;
	data->tex_x = fmax(0, fmin(data->tex->width - 1, data->tex_x));
	ft_paint(data, distance, screen_x);
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