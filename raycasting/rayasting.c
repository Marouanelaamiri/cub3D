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

	static void put_pixel(char *data, int x, int y, int color, int line_len,
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

	static float cast_ray(t_data *data, float angle)
	{
		float	px;
		float	py;
		float	x;
		float	y;

		px = data->player_x * TILE_SIZE + TILE_SIZE / 2;
		py = data->player_y * TILE_SIZE + TILE_SIZE / 2;
		x = px;
		y = py;
		while (1)
		{
			int	tile_x = (int)(x / TILE_SIZE);
			int	tile_y = (int)(y / TILE_SIZE);

			if (tile_x < 0 || tile_y < 0 || tile_y >= data->recmap_height ||
				tile_x >= (int)ft_strlen(data->map[tile_y]) ||
				data->map[tile_y][tile_x] == '1')
				break ;
			x += cosf(angle);
			y += sinf(angle);
		}
		float dx = x - px;
		float dy = y - py;
		return (sqrtf(dx * dx + dy * dy));
	}

	static void draw_column(t_data *data, int col, float dist, int screen_width,
							int screen_height)
	{
		int	wall_height;
		int	wall_top;
		int	wall_bottom;
		int	y;
		int	color;

		wall_height = (int)((TILE_SIZE * screen_height) / (dist + 0.0001));
		if (wall_height > screen_height)
			wall_height = screen_height;
		wall_top = (screen_height / 2) - (wall_height / 2);
		wall_bottom = wall_top + wall_height;
		y = 0;
		while (y < screen_height)
		{
			if (y < wall_top)
				color = COLOR_BLACK;
			else if (y >= wall_top && y <= wall_bottom)
				color = COLOR_RED;
			else
				color = COLOR_BLACK;
			put_pixel(data->addr, col, y, color, data->line_len, data->bpp,
					screen_width, screen_height);
			y++;
		}
	}

	static void render_3d(t_data *data)
	{
		int		w;
		int		h;
		float	step;
		float	angle;
		int		col;

		w = data->recmap_with * TILE_SIZE;
		h = data->recmap_height * TILE_SIZE;
		step = data->fov / w;
		angle = data->ray_angle - (data->fov / 2);
		col = 0;
		while (col < w)
		{
			float	dist = cast_ray(data, angle);
			dist *= cosf(angle - data->ray_angle); // fish-eye fix
			draw_column(data, col, dist, w, h);
			angle += step;
			col++;
		}
	}

	static void redraw(t_data *data)
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

	// Collision check: returns 1 if position is a wall, 0 otherwise
	static int is_wall(t_data *data, float x, float y)
	{
		int	tile_x;
		int	tile_y;

		tile_x = (int)x;
		tile_y = (int)y;
		if (tile_y < 0 || tile_y >= data->recmap_height)
			return (1);
		if (tile_x < 0 || tile_x >= (int)ft_strlen(data->map[tile_y]))
			return (1);
		return (data->map[tile_y][tile_x] == '1');
	}

	void key_hook(void *param)
	{
		t_data	*data = (t_data *)param;
		float	new_x ;
		float	new_y ;

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

