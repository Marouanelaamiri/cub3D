	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   rayasting.c                                        :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
	/*   Updated: 2025/07/16 22:28:53 by aromani          ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "../includes/cub3d.h"

float	get_angle_from_dir(char dir)
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

void	set_char(t_data *data, char c)
{
	data->player_char = c;
}

void	set_fov(t_data *data, float fov)
{
	data->fov = fov;
}

static void	set_wh_map(t_data *data)
{
	int	y;
	int	max_width;

	y = 0;
	max_width = 0;
	while (data->map[y])
	{
		int	x;
		int	width;

		x = 0;
		width = 0;
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

/* ************************************************************************** */
/* 3) RAYCASTER — record hit_side & hit_wall_x                                */
/* ************************************************************************** */
static float	cast_ray(t_data *data, float angle)
{
	float	px;
	float	py;
	float	x;
	float	y;
	float	dx;
	float	dy;

	px = data->player_x * TILE_SIZE + TILE_SIZE / 2;
	py = data->player_y * TILE_SIZE + TILE_SIZE / 2;
	x = px;
	y = py;
	while (1)
	{
		int	tile_x;
		int	tile_y;

		tile_x = (int)(x / TILE_SIZE);
		tile_y = (int)(y / TILE_SIZE);
		if (tile_x < 0 || tile_y < 0
			|| tile_y >= data->recmap_height
			|| tile_x >= (int)ft_strlen(data->map[tile_y])
			|| data->map[tile_y][tile_x] == '1')
			break ;
		x += cosf(angle);
		y += sinf(angle);
	}
	/* decide which side was hit */
	if (fabsf(cosf(angle)) > fabsf(sinf(angle)))
	{
		/* vertical wall (E/W) */
		if (cosf(angle) > 0)
			data->hit_side = 'E';
		else
			data->hit_side = 'W';
		data->hit_wall_x = fmodf(y, TILE_SIZE) / TILE_SIZE;
	}
	else
	{
		/* horizontal wall (N/S) */
		if (sinf(angle) > 0)
			data->hit_side = 'S';
		else
			data->hit_side = 'N';
		data->hit_wall_x = fmodf(x, TILE_SIZE) / TILE_SIZE;
	}
	/* finally return distance (without fish-eye) */
	dx = x - px;
	dy = y - py;
	return (sqrtf(dx * dx + dy * dy));
}

/* ************************************************************************** */
/* 4) DRAW COLUMN — sample from textures                                     */
/* ************************************************************************** */
static void	draw_column(t_data *data,
				int col, float dist,
				int screen_w, int screen_h)
{
	int			wall_h;
	int			top;
	int			bottom;
	int			y;
	uint32_t	color;
	int			tw;
	int			th;
	uint32_t	*pxs;

	/* compute wall slice height */
	wall_h = (int)((TILE_SIZE * screen_h) / (dist + 0.0001f));
	if (wall_h > screen_h)
		wall_h = screen_h;
	top = (screen_h - wall_h) / 2;
	bottom = top + wall_h - 1;

	/* pick correct texture */
	if (data->hit_side == 'N')
		data->tex = data->no;
	else if (data->hit_side == 'S')
		data->tex = data->so;
	else if (data->hit_side == 'W')
		data->tex = data->we;
	else
		data->tex = data->ea;

	tw = data->tex->width;
	th = data->tex->height;
	pxs = (uint32_t *)data->tex->pixels;

	/* horizontal offset in texture */
	data->tex_x = (int)(data->hit_wall_x * (float)tw);
	if (data->hit_side == 'S' || data->hit_side == 'E')
		data->tex_x = tw - data->tex_x - 1;
	if (data->tex_x < 0)
		data->tex_x = 0;
	if (data->tex_x >= tw)
		data->tex_x = tw - 1;

	y = 0;
	while (y < screen_h)
	{
		if (y < top)
			color = data->c_color;
		else if (y <= bottom)
		{
			/* vertical offset in texture */
			data->tex_y = (y - top) * th / wall_h;
			if (data->tex_y < 0)
				data->tex_y = 0;
			if (data->tex_y >= th)
				data->tex_y = th - 1;
			color = pxs[(int) (data->tex_y * tw + data->tex_x)];
		}
		else
			color = data->f_color;

		put_pixel(data->addr, col, y, color,
				  data->line_len, data->bpp,
				  screen_w, screen_h);
		y++;
	}
}

/* ************************************************************************** */
/* 5) RENDER LOOP — sample & fish-eye fix                                     */
/* ************************************************************************** */
static void	render_3d(t_data *data)
{
	int		w;
	int		h;
	float	step;
	float	angle;
	int		col;
	float	dist;

	w = data->recmap_with * TILE_SIZE;
	h = data->recmap_height * TILE_SIZE;
	step = data->fov / (float)w;
	angle = data->ray_angle - (data->fov / 2);
	col = 0;
	while (col < w)
	{
		dist = cast_ray(data, angle);
		// dist = dist * cosf(angle - data->ray_angle);
		draw_column(data, col, dist, w, h);
		angle += step;
		col++;
	}
}

static void	redraw(t_data *data)
{
	int	width;
	int	height;

	width = data->recmap_with * TILE_SIZE;
	height = data->recmap_height * TILE_SIZE;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, width, height);
	data->addr = (char *)data->img->pixels;
	data->line_len = data->img->width * 4;
	render_3d(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

static int	is_wall(t_data *data, float x, float y)
{
	int	tx;
	int	ty;

	tx = (int)x;
	ty = (int)y;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->ray_angle -= 0.05f;
		if (data->ray_angle < 0)
			data->ray_angle += 2 * M_PI;
		redraw(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->ray_angle += 0.05f;
		if (data->ray_angle >= 2 * M_PI)
			data->ray_angle -= 2 * M_PI;
		redraw(data);
	}
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = data->player_x - cosf(data->ray_angle) * SPEED;
		new_y = data->player_y - sinf(data->ray_angle) * SPEED;
		if (!is_wall(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
		redraw(data);
	}
}

char	*ft_strdupv2(char *str)
{
		int		i;
		int		j;
		int		len;
		int		end;
		char	*dup;

		i = 0;
		j = 0;
		len = 0;
		end = 0;
		while (str[end])
			end++;
		end--;
		while (str[end] && (str[end] == ' ' || str[end] == '\t'))
			end--;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		len = end - i + 1;
		dup = malloc(len + 1);
		if (!dup)
			return (NULL);
		while (i <= end)
			dup[j++] = str[i++];
		dup[j] = '\0';
		return (dup);
	}

	void prepare_new_map(t_data *data)
	{
		int		i;
		char	**new_str;

		i = 0;
		new_str = malloc((data->recmap_height + 1) * sizeof(char *));
		if (!new_str)
			return ;
		while (i < data->recmap_height)
		{
			new_str[i] = ft_strdupv2(data->map[i]);
			i++;
		}
		new_str[i] = NULL;
		data->map = new_str;
	}

	int put_map_2dv(t_data *data)
	{
		set_wh_map(data);
		prepare_new_map(data);
		int width = data->recmap_with * TILE_SIZE;
		int height = data->recmap_height * TILE_SIZE;
		data->mlx = mlx_init(width, height, "Cub3D Fake 3D", false);
		if (!data->mlx)
			return (1);
		if (load_textures(data))
			return (1);
		data->img = mlx_new_image(data->mlx, width, height);
		if (!data->img)
			return (1);
		data->addr = (char *)data->img->pixels;
		data->bpp = 32;
		data->line_len = data->img->width * 4;
		data->endian = 0;
		data->fov = M_PI / 3; // 60 degrees

		int y = 0;
		while (y < data->recmap_height)
		{
			int x = 0;
			while (data->map[y][x])
			{
				char c = data->map[y][x];
				if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				{
					set_char(data, c);
					data->player_x = x;
					data->player_y = y;
					data->ray_angle = get_angle_from_dir(c);
				}
				x++;
			}
			y++;
		}
		redraw(data);
		mlx_loop_hook(data->mlx, key_hook, data);
		mlx_loop(data->mlx);
		return (0);
	}
