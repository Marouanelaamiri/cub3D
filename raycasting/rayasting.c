/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:21:26 by aromani           #+#    #+#             */
/*   Updated: 2025/07/14 15:04:04 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_wh_map(t_data *data)
{
	int	y = 0;
	int	max_width = 0;

	while (data->map[y])
	{
		int x = 0;
		int line_width = 0;

		while (data->map[y][x])
		{
			if (data->map[y][x] != ' ' && data->map[y][x] != '\t')
				line_width++;
			x++;
		}
		if (line_width > max_width)
			max_width = line_width;
		y++;
	}
	data->recmap_height = y;
	data->recmap_with = max_width;
}

static void put_pixel(char *data, int x, int y, int color, int line_length, int bpp)
{
    if (x < 0 || y < 0 || x * (bpp / 8) >= line_length || y * line_length >= line_length * TILE_SIZE * 100)
		return;
	int offset = y * line_length + x * (bpp / 8);
	data[offset + 0] = color & 0xFF;
	data[offset + 1] = (color >> 8) & 0xFF;
	data[offset + 2] = (color >> 16) & 0xFF;
	data[offset + 3] = (color >> 24) & 0xFF;
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

static void draw_tile(t_data *data, int tile_x, int tile_y, int color)
{
	int y = 0;
	while (y < TILE_SIZE)
	{
		int x = 0;
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

char *ft_strdupv2(char *str)
{
	char *dup;
	int i = 0;
	int j = 0;
	int len = 0;
	int end = 0;
	
	while (str[end])
		end ++;
	end --;
	while (str[end] && (str[end] == ' ' || str[end] == '\t'))
		end --;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	int k = i;
	while (str[k])
	{
		//if (str[k] != ' ' && str[k] != '\t')
			len++;
		k++;
	}

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (str[i] && i <= end)
	{
		//if (str[i] != ' ' && str[i] != '\t')
			dup[j++] = str[i];
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

void prepare_new_map(t_data *data)
{
	char **new_str;
	int i;

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

float get_angle_from_dir(char dir)
{
	if (dir == 'N')
		return M_PI / 2;   // 90°
	if (dir == 'S')
		return 3 * M_PI / 2; // 270°
	if (dir == 'E')
		return 0;
	if (dir == 'W')
		return M_PI;
	return 0;
}

void set_char(t_data *data, char c)
{
	data->player_char = c;
	return ;
}

int put_map_2dv(t_data *data)
{
	
	set_wh_map(data);
	prepare_new_map(data);
	data->mlx = mlx_init(data->recmap_with * TILE_SIZE,
						 data->recmap_height * TILE_SIZE,
						 "Cub3D Map",
						 false);
	if (!data->mlx)
		return (1);

	data->img = mlx_new_image(data->mlx,
							  data->recmap_with * TILE_SIZE,
							  data->recmap_height * TILE_SIZE);
	if (!data->img)
		return (1);

	data->addr = (char *)data->img->pixels;
	data->bpp = 32;
	data->line_len = data->img->width * 4;
	data->endian = 0;

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
			draw_tile(data, x, y, COLOR_BLACK);
            draw_player(data, x, y, COLOR_WHITE);
		}
        else if (c == '1')
            draw_tile(data, x, y, COLOR_RED);
        else if (c == '0')
            draw_tile(data, x, y, COLOR_BLACK);
        x++;
    }
    y++;
    }

	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}

