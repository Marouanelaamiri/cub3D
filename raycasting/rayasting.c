/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/01 20:36:08 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

float get_angle_from_dir(char dir) {
	if (dir == 'N') return (M_PI / 2);
	if (dir == 'S') return (3 * M_PI / 2);
	if (dir == 'E') return (0);
	if (dir == 'W') return (M_PI);
	return (0);
}

void set_char(t_data *data, char c) {
	data->player_char = c;
}

void set_fov(t_data *data, float fov) {
	data->fov = fov;
}

static void set_wh_map(t_data *data) {
	int y = 0;
	int max_width = 0;
	while (data->map[y]) {
		int x = 0;
		int width = 0;
		while (data->map[y][x]) {
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

static float	cast_ray(t_data *data, float angle)
{
	float	px = data->player_x * TILE_SIZE + TILE_SIZE / 2;
	float	py = data->player_y * TILE_SIZE + TILE_SIZE / 2;
	float	dir_x = cosf(angle);
	float	dir_y = sinf(angle);

	int	map_x = (int)(px / TILE_SIZE);
	int	map_y = (int)(py / TILE_SIZE);

	float	delta_x = fabsf(1 / dir_x);
	float	delta_y = fabsf(1 / dir_y);

	int	step_x = (dir_x < 0) ? -1 : 1;
	int	step_y = (dir_y < 0) ? -1 : 1;

	float	side_dist_x = (step_x < 0)
		? (px - map_x * TILE_SIZE) * delta_x
		: ((map_x + 1) * TILE_SIZE - px) * delta_x;
	float	side_dist_y = (step_y < 0)
		? (py - map_y * TILE_SIZE) * delta_y
		: ((map_y + 1) * TILE_SIZE - py) * delta_y;

	int	hit = 0;
	int	side;

	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x * TILE_SIZE;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_y * TILE_SIZE;
			map_y += step_y;
			side = 1;
		}
		if (map_y < 0 || map_y >= data->recmap_height
			|| map_x < 0 || map_x >= (int)ft_strlen(data->map[map_y])
			|| data->map[map_y][map_x] == '1')
			hit = 1;
	}

	float hit_dist = (side == 0)
		? (side_dist_x - delta_x * TILE_SIZE)
		: (side_dist_y - delta_y * TILE_SIZE);

	if (side == 0)
	{
		data->hit_side = (step_x > 0) ? 'E' : 'W';
		float wall_y = py + hit_dist * dir_y;
		data->hit_wall_x = fmodf(wall_y, TILE_SIZE) / TILE_SIZE;
	}
	else
	{
		data->hit_side = (step_y > 0) ? 'S' : 'N';
		float wall_x = px + hit_dist * dir_x;
		data->hit_wall_x = fmodf(wall_x, TILE_SIZE) / TILE_SIZE;
	}
	return hit_dist;
}


static void	put_pixel(char *data, int x, int y,
			uint32_t color, int line_len,
			int bpp, int width, int height)
{
	int	offset;

	if (x < 0 || y < 0 || x >= width || y >= height)
		return ;
	offset = y * line_len + x * (bpp / 8);
	data[offset + 0] = color & 0xFF;
	data[offset + 1] = (color >> 8) & 0xFF;
	data[offset + 2] = (color >> 16) & 0xFF;
	data[offset + 3] = (color >> 24) & 0xFF;
}

static void draw_column(t_data *data, int col, float dist)
{
	int			wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / (dist + 0.0001f));
	int			top = (MAP_HEIGHT - wall_h) / 2;
	int			bottom = top + wall_h - 1;
	int			y = 0;
	uint32_t	color;

	if (data->hit_side == 'N') data->tex = data->no;
	else if (data->hit_side == 'S') data->tex = data->so;
	else if (data->hit_side == 'W') data->tex = data->we;
	else                            data->tex = data->ea;

	int			tw = data->tex->width;
	int			th = data->tex->height;
	uint32_t	*pxs = (uint32_t *)data->tex->pixels;

	if (wall_h > MAP_HEIGHT) wall_h = MAP_HEIGHT;

	data->tex_x = (int)(data->hit_wall_x * (float)tw);
	if (data->hit_side == 'S' || data->hit_side == 'E')
		data->tex_x = tw - data->tex_x - 1;
	if (data->tex_x < 0)    data->tex_x = 0;
	if (data->tex_x >= tw) data->tex_x = tw - 1;

	while (y < MAP_HEIGHT)
	{
		if (y < top)
			color = data->c_color;
		else if (y <= bottom)
		{
			data->tex_y = (y - top) * th / wall_h;
			if (data->tex_y < 0)    data->tex_y = 0;
			if (data->tex_y >= th) data->tex_y = th - 1;
			color = pxs[(int)(data->tex_y * tw + data->tex_x)];
		}
		else
			color = data->f_color;
		put_pixel(data->addr, col, y, color,
				  data->line_len, data->bpp,
				  MAP_HEIGHT * TILE_SIZE , MAP_HEIGHT *TILE_SIZE);
		//put_pixel(data, col, y, color, data->line_len, data->bpp);
		++y;
	}
}

static void	render_3d(t_data *data)
{
	int		w     = MAP_WIDTH;
	float	step  = data->fov / (float)w;
	float	angle = data->ray_angle - (data->fov / 2);
	int		col   = 0;

	while (col < w)
	{
		float dist = cast_ray(data, angle);
		dist *= cosf(angle - data->ray_angle);
		draw_column(data, col, dist);
		angle += step;
		++col;
	}
}

static void	redraw(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	data->img      = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	data->addr     = (char *)data->img->pixels;
	data->bpp      = 32;
	data->line_len = data->img->width * 4;
	render_3d(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

static int	is_wall(t_data *data, float x, float y)
{
	int tx = (int)x;
	int ty = (int)y;

	if (ty < 0 || ty >= data->recmap_height) 
		return (1);
	if (tx < 0 || tx >= (int)ft_strlen(data->map[ty])) 
		return (1);
	return (data->map[ty][tx] == '1');
}

void	key_hook(void *param)
{
	t_data	*data;
	float	new_x;
	float	new_y;

	data = (t_data *)param;
	
 	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		new_x = data->player_x + cosf(data->ray_angle) * SPEED;
		new_y = data->player_y + sinf(data->ray_angle) * SPEED;
		if (!is_wall(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
		redraw(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = data->player_x - cosf(data->ray_angle) * SPEED;
		new_y = data->player_y - sinf(data->ray_angle) * SPEED;
		if (!is_wall(data, new_x , new_y ))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
		redraw(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A)) // strafe left
	{
		new_x = data->player_x + cosf(data->ray_angle - M_PI_2) * SPEED;
		new_y = data->player_y + sinf(data->ray_angle - M_PI_2) * SPEED;
		if (!is_wall(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
		redraw(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D)) // strafe right
	{
		new_x = data->player_x + cosf(data->ray_angle + M_PI_2) * SPEED;
		new_y = data->player_y + sinf(data->ray_angle + M_PI_2) * SPEED;
		if (!is_wall(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
		redraw(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->ray_angle -= 0.05f;
		if (data->ray_angle < 0)
			data->ray_angle += 2 * M_PI;
		redraw(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->ray_angle += 0.05f;
		if (data->ray_angle >= 2 * M_PI)
			data->ray_angle -= 2 * M_PI;
		redraw(data);
	}
	return ;
}


void	terminate_program(void *param)
{
	t_data *data = (t_data *)param;
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	exit(0);
}

int	put_map_2dv(t_data *data)
{
	set_wh_map(data);
	data->mlx = mlx_init(MAP_WIDTH, MAP_HEIGHT, "Cub3D Fake 3D", false);
	if (!data->mlx) return (1);
	if (load_textures(data)) return (1);

	data->img      = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	data->addr     = (char *)data->img->pixels;
	data->bpp      = 32;
	data->line_len = data->img->width * 4;
	data->endian   = 0;
	data->fov      = FOV;

	int iy = 0;
	while (iy < data->recmap_height)
	{
		int ix = 0;
		while (data->map[iy][ix])
		{
			if (ft_strchr("NSWE", data->map[iy][ix]))
			{
				data->player_x  = ix;
				data->player_y  = iy;
				data->ray_angle = get_angle_from_dir(data->map[iy][ix]);
			}
			ix++;
		}
		iy++;
	}

	redraw(data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_close_hook(data->mlx, terminate_program, data);
	mlx_loop(data->mlx);
	return (0);
}
