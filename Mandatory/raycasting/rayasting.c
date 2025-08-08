/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/08 16:59:35 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

float get_angle_from_dir(char dir) 
{
	if (dir == 'N') 
		return (M_PI / 2);
	if (dir == 'S') 
		return (3 * M_PI / 2);
	if (dir == 'E') 
		return (0);
	if (dir == 'W') 
		return (M_PI);
	return (0);
}

void set_char(t_data *data, char c) 
{
	data->player_char = c;
}

void set_fov(t_data *data, float fov) 
{
	data->fov = fov;
}

static void set_wh_map(t_data *data) 
{
	int y = 0;
	int max_width = 0;
	while (data->map[y]) 
	{
		int x = 0;
		int width = 0;
		while (data->map[y][x]) 
		{
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

void init_algo(t_data *data, float angle)
{
	data->algo->px = data->player_x * TILE_SIZE + TILE_SIZE / 2;
	data->algo->py = data->player_y * TILE_SIZE + TILE_SIZE / 2;
	data->algo->dir_x = cosf(angle);
	data->algo->dir_y = sinf(angle);
	data->algo->map_x = (int)(data->algo->px / TILE_SIZE);
	data->algo->map_y = (int)(data->algo->py / TILE_SIZE);
	data->algo->delta_x = fabsf(1 / data->algo->dir_x);
	data->algo->delta_y = fabsf(1 / data->algo->dir_y);
	if (data->algo->dir_x < 0)
		data->algo->step_x = -1;
	else
		data->algo->step_x = 1;
	if (data->algo->dir_y < 0)
		data->algo->step_y = -1;
	else
		data->algo->step_y = 1;
	if (data->algo->step_x < 0)
		data->algo->side_dist_x = (data->algo->px - data->algo->map_x * TILE_SIZE) * data->algo->delta_x;
	else
		data->algo->side_dist_x = ((data->algo->map_x + 1) * TILE_SIZE - data->algo->px) * data->algo->delta_x;
	if (data->algo->step_y < 0)
		data->algo->side_dist_y = (data->algo->py - data->algo->map_y * TILE_SIZE) * data->algo->delta_y;
	else
		data->algo->side_dist_y = ((data->algo->map_y + 1) * TILE_SIZE - data->algo->py) * data->algo->delta_y;

}

void send_ray(t_data *data)
{
	int	hit = 0;
	
	while (!hit)
	{
		if (data->algo->side_dist_x < data->algo->side_dist_y)
		{
			data->algo->side_dist_x += data->algo->delta_x * TILE_SIZE;
			data->algo->map_x += data->algo->step_x;
			data->algo->side = 0;
		}
		else
		{
			data->algo->side_dist_y += data->algo->delta_y * TILE_SIZE;
			data->algo->map_y += data->algo->step_y;
			data->algo->side = 1;
		}
		if (data->algo->map_y < 0 || data->algo->map_y >= data->recmap_height
			|| data->algo->map_x < 0 || data->algo->map_x >= (int)ft_strlen(data->map[data->algo->map_y])
			|| data->map[data->algo->map_y][data->algo->map_x] == '1')
			hit = 1;
	}
} 

void texters_count(t_data *data, float hit_dist)
{
	float wall_x;
	float wall_y;

	wall_x	= 0.0;
	wall_y	= 0.0;
	if (data->algo->side == 0)
	{
		if (data->algo->step_x > 0)
    		data->hit_side = 'E';
		else
   			data->hit_side = 'W';
		wall_y = data->algo->py + hit_dist * data->algo->dir_y;
		data->hit_wall_x = fmodf(wall_y, TILE_SIZE) / TILE_SIZE;
	}
	else
	{
		if (data->algo->step_y > 0) 
			data->hit_side = 'S'; 
		else 
			data->hit_side = 'N';
		wall_x = data->algo->px + hit_dist * data->algo->dir_x;
		data->hit_wall_x = fmodf(wall_x, TILE_SIZE) / TILE_SIZE;
	}
}

static float	cast_ray(t_data *data, float angle)
{
	float hit_dist;
	ft_memset(data->algo,0,sizeof(t_algo));
	init_algo(data, angle);
	send_ray(data);
	if (data->algo->side == 0)
		hit_dist = data->algo->side_dist_x - data->algo->delta_x * TILE_SIZE;
	else
		hit_dist = data->algo->side_dist_y - data->algo->delta_y * TILE_SIZE;
	texters_count(data, hit_dist);
	return (hit_dist);
}

void init_struct(t_data *data)
{
	data->img      = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	data->addr     = (char *)data->img->pixels;
	data->bpp      = 32;
	data->line_len = data->img->width * 4;
	data->endian   = 0;
	data->fov      = FOV;
}

static void	put_pixel(t_data *d, int x, int y,
			uint32_t color)
{
	int	offset;
	char *data;

	data = (char *)d->addr;
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
		return ;
	offset = y * d->line_len + x * (d->bpp / 8);
	data[offset + 0] = color & 0xFF;
	data[offset + 1] = (color >> 8) & 0xFF;
	data[offset + 2] = (color >> 16) & 0xFF;
	data[offset + 3] = (color >> 24) & 0xFF;
}

void init_texters(t_data *data)
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

void ft_paint(t_data *data, uint32_t *pxs, float dist, int col)
{
	int wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / fmaxf(dist, 0.1f));
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

static void	redraw(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	init_struct(data);
	render_3d(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

static int is_colliding(t_data *data, float new_px, float new_py)
{

    int tile_x = (int)new_px;
    int tile_y = (int)new_py;
    if (tile_y >= 0 && tile_y < data->recmap_height
     && tile_x >= 0 && tile_x < (int)ft_strlen(data->map[tile_y])
     && data->map[tile_y][tile_x] == '1')
    {
        return 1;
    }
    const float px = new_px * TILE_SIZE + (TILE_SIZE / 2.0f);
    const float py = new_py * TILE_SIZE + (TILE_SIZE / 2.0f);
    const float r  = COLLIDE_PAD * TILE_SIZE;
    float corners[4][2] = {
        { px - r, py - r },
        { px + r, py - r },
        { px - r, py + r },
        { px + r, py + r }
    };
    for (int i = 0; i < 4; ++i)
    {
        int mx = (int)(corners[i][0] / TILE_SIZE);
        int my = (int)(corners[i][1] / TILE_SIZE);
        if (my < 0 || my >= data->recmap_height
         || mx < 0 || mx >= (int)ft_strlen(data->map[my])
         || data->map[my][mx] == '1')
            return 1;
    }
    return 0;
}

void terminate_program(void *param)
{
    t_data *data = (t_data *)param;
    if (data->img)
        mlx_delete_image(data->mlx, data->img);
    if (data->mlx)
        mlx_terminate(data->mlx);
    exit(0);
}

int ft_retate(t_data *data, int flag)
{
	int changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->ray_angle -= 0.05f;
		if (data->ray_angle < 0)
			data->ray_angle += 2 * M_PI;
		changed = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->ray_angle += 0.05f;
		if (data->ray_angle >= 2 * M_PI)
			data->ray_angle -= 2 * M_PI;
		changed = 1;
	}
	if (flag == 1)
		return (1);
	return (changed);
}

int key_w(t_data *data, int flag, float new_x, float new_y)
{
	int changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		new_x = data->player_x + cosf(data->ray_angle) * SPEED;
		new_y = data->player_y + sinf(data->ray_angle) * SPEED;
		if (!is_colliding(data, new_x, data->player_y))
		{
			data->player_x = new_x;
			changed = 1;
		}
		if (!is_colliding(data, data->player_x, new_y))
		{
			data->player_y = new_y;
			changed = 1;
		}
	}
	if (flag == 1)
		return (1);
	return (changed);
}

int key_s(t_data *data, int flag, float new_x, float new_y)
{
	int changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = data->player_x - cosf(data->ray_angle) * SPEED;
		new_y = data->player_y - sinf(data->ray_angle) * SPEED;
		if (!is_colliding(data, new_x, data->player_y))
		{
			data->player_x = new_x;
			changed = 1;
		}
		if (!is_colliding(data, data->player_x, new_y))
		{
			data->player_y = new_y;
			changed = 1;
		}
	}
	if (flag == 1)
		return (1);
	return (changed);
}

int key_a(t_data *data, int flag, float new_x, float new_y)
{
	int changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		new_x = data->player_x + cosf(data->ray_angle - M_PI_2) * SPEED;
		new_y = data->player_y + sinf(data->ray_angle - M_PI_2) * SPEED;
		if (!is_colliding(data, new_x, data->player_y))
		{
			data->player_x = new_x;
			changed = 1;
		}
		if (!is_colliding(data, data->player_x, new_y))
		{
			data->player_y = new_y;
			changed = 1;
		}
	}
	if (flag == 1)
		return (1);
	return (changed);
}

int key_d(t_data *data, int flag, float new_x, float new_y)
{
	int changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		new_x = data->player_x + cosf(data->ray_angle + M_PI_2) * SPEED;
		new_y = data->player_y + sinf(data->ray_angle + M_PI_2) * SPEED;
		if (!is_colliding(data, new_x, data->player_y))
		{
			data->player_x = new_x;
			changed = 1;
		}
		if (!is_colliding(data, data->player_x, new_y))
		{
			data->player_y = new_y;
			changed = 1;
		}
	}
	if (flag == 1)
		return (1);
	return (changed);
}

void	key_hook(void *param)
{
	t_data	*data = (t_data *)param;
	float	new_x;
	float	new_y;
	int		changed;

	new_x = 0.0;
	new_y = 0.0;
	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		terminate_program(param);
	changed = key_w(data, changed, new_x, new_y);
	changed = key_s(data, changed, new_x, new_y);
	changed = key_a(data, changed, new_x, new_y);
	changed = key_d(data, changed, new_x, new_y);
	changed = ft_retate(data, changed);
	if (changed)
		redraw(data);
}

void init_player(t_data *data)
{
	int	iy;
	int	ix;
	
	iy = 0;
	while (iy < data->recmap_height)
	{
		ix = 0;
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
}

void ff()
{
	system("leaks cub3D");
}

int	put_map_2dv(t_data *data)
{
	//atexit(ff);
	set_wh_map(data);
	data->mlx = mlx_init(MAP_WIDTH, MAP_HEIGHT, "Cub3D", false);
	if (!data->mlx) 
		return (1);
	if (load_textures(data)) 
		return (1);
	init_struct(data);
	init_player(data);
	redraw(data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_close_hook(data->mlx, terminate_program, data);
	mlx_loop(data->mlx);
	return (0);
}
