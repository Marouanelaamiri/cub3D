/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/07 20:26:05 by aromani          ###   ########.fr       */
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

static float	cast_ray(t_data *data, float angle)
{
	float hit_dist;
	float	px = data->player_x * TILE_SIZE + TILE_SIZE / 2;
	float	py = data->player_y * TILE_SIZE + TILE_SIZE / 2;
	float	dir_x = cosf(angle);
	float	dir_y = sinf(angle);

	int	map_x = (int)(px / TILE_SIZE);
	int	map_y = (int)(py / TILE_SIZE);
	
	float	delta_x = fabsf(1 / dir_x);
	float	delta_y = fabsf(1 / dir_y);

	int step_x;
	if (dir_x < 0)
		step_x = -1;
	else
		step_x = 1;

	int step_y;
	if (dir_y < 0)
		step_y = -1;
	else
		step_y = 1;

	float side_dist_x;
	if (step_x < 0)
		side_dist_x = (px - map_x * TILE_SIZE) * delta_x;
	else
		side_dist_x = ((map_x + 1) * TILE_SIZE - px) * delta_x;

	float side_dist_y;
	if (step_y < 0)
		side_dist_y = (py - map_y * TILE_SIZE) * delta_y;
	else
		side_dist_y = ((map_y + 1) * TILE_SIZE - py) * delta_y;


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


	if (side == 0)
		hit_dist = side_dist_x - delta_x * TILE_SIZE;
	else
		hit_dist = side_dist_y - delta_y * TILE_SIZE;

	if (side == 0)
	{
		if (step_x > 0)
    		data->hit_side = 'E';
		else
   			data->hit_side = 'W';

		float wall_y = py + hit_dist * dir_y;
		data->hit_wall_x = fmodf(wall_y, TILE_SIZE) / TILE_SIZE;
	}
	else
	{
		if (step_y > 0) 
			data->hit_side = 'S'; 
		else 
			data->hit_side = 'N';
		float wall_x = px + hit_dist * dir_x;
		data->hit_wall_x = fmodf(wall_x, TILE_SIZE) / TILE_SIZE;
	}
	return hit_dist;
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
    const float min_dist = 0.1f;
    int wall_h = (int)((TILE_SIZE * MAP_HEIGHT) / fmaxf(dist, min_dist));
    int top = (MAP_HEIGHT - wall_h) / 2;
    int bottom = top + wall_h;

    if (data->hit_side == 'N') 
        data->tex = data->no;
    else if (data->hit_side == 'S') 
        data->tex = data->so;
    else if (data->hit_side == 'W') 
        data->tex = data->we;
    else                            
        data->tex = data->ea;
    const int tw = data->tex->width;
    const int th = data->tex->height;
    uint32_t *pxs = (uint32_t *)data->tex->pixels;
	
    float wall_x = fmodf(data->hit_wall_x, TILE_SIZE);
    if (wall_x < 0)
		wall_x += TILE_SIZE;
    data->tex_x = (int)(wall_x * tw);
    
    if (data->hit_side == 'S' || data->hit_side == 'E')
        data->tex_x = tw - data->tex_x - 1;
        data->tex_x = fmax(0, fmin(tw - 1, data->tex_x));

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        if (y < top)
        {
            mlx_put_pixel(data->img, col, y, data->c_color);
        }
        else if (y > top && y < bottom)
        {
            float ratio = (float)(y - top) / wall_h;
            int tex_y = (int)(ratio * (th - 1));
            tex_y = fmax(0, fmin(th - 1, tex_y));
            int tex_index = tex_y * tw + data->tex_x;
            uint32_t color =  pxs[tex_index] ;
            put_pixel((char *)data->addr, col, y, color,
                     data->line_len, data->bpp, MAP_WIDTH, MAP_HEIGHT);
        }
        else if (y > bottom)
        {
            mlx_put_pixel(data->img, col, y, data->f_color);
        }
    }
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

void	key_hook(void *param)
{
	t_data	*data = (t_data *)param;
	float	new_x;
	float	new_y;
	int		changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		terminate_program(param);

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

	/* ─── Strafe Right (D) ──────────────────────────────────── */
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

	/* ─── Rotate Left ◀ ────────────────────────────────────── */
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->ray_angle -= 0.05f;
		if (data->ray_angle < 0)
			data->ray_angle += 2 * M_PI;
		changed = 1;
	}

	/* ─── Rotate Right ▶ ───────────────────────────────────── */
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->ray_angle += 0.05f;
		if (data->ray_angle >= 2 * M_PI)
			data->ray_angle -= 2 * M_PI;
		changed = 1;
	}

	if (changed)
		redraw(data);
}

// void init_struct(t_data *data)
// {
// 	data->img      = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
// 	data->addr     = (char *)data->img->pixels;
// 	data->bpp      = 32;
// 	data->line_len = data->img->width * 4;
// 	data->endian   = 0;
// 	data->fov      = FOV;
// }

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
	atexit(ff);
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
