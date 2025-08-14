/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:27:02 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/14 22:21:24 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_frames(t_data *data)
{
	data->reload_frames[0] = mlx_load_png("Bonus/textures/reload2/0.png");
	data->reload_frames[1] = mlx_load_png("Bonus/textures/reload2/1.png");
	data->reload_frames[2] = mlx_load_png("Bonus/textures/reload2/2.png");
	data->reload_frames[3] = mlx_load_png("Bonus/textures/reload2/3.png");
	data->reload_frames[4] = mlx_load_png("Bonus/textures/reload2/4.png");
	data->reload_frames[5] = mlx_load_png("Bonus/textures/reload2/5.png");
	data->reload_frames[6] = mlx_load_png("Bonus/textures/reload2/6.png");
	data->reload_frames[7] = mlx_load_png("Bonus/textures/reload2/7.png");
	data->reload_frames[8] = mlx_load_png("Bonus/textures/reload2/8.png");
	data->reload_frames[9] = mlx_load_png("Bonus/textures/reload2/9.png");
	data->reload_frames[10] = mlx_load_png("Bonus/textures/reload2/10.png");
	data->reload_frames[11] = mlx_load_png("Bonus/textures/reload2/11.png");
	data->reload_frames[12] = mlx_load_png("Bonus/textures/reload2/12.png");
	data->reload_frames[13] = mlx_load_png("Bonus/textures/reload2/13.png");
	data->reload_frames[14] = mlx_load_png("Bonus/textures/reload2/14.png");
	data->reload_frames[15] = mlx_load_png("Bonus/textures/reload2/15.png");
	data->reload_frames[16] = mlx_load_png("Bonus/textures/reload2/16.png");
	data->reload_frames[17] = mlx_load_png("Bonus/textures/reload2/17.png");
	data->reload_frames[18] = mlx_load_png("Bonus/textures/reload2/18.png");
	data->reload_frames[19] = mlx_load_png("Bonus/textures/reload2/20.png");
	data->reload_frames[20] = mlx_load_png("Bonus/textures/reload2/21.png");
	data->reload_frames[21] = mlx_load_png("Bonus/textures/reload2/22.png");
	data->reload_frames[22] = mlx_load_png("Bonus/textures/reload2/23.png");
	data->reload_frames[23] = mlx_load_png("Bonus/textures/reload2/24.png");
	data->reload_frames[24] = mlx_load_png("Bonus/textures/reload2/25.png");
}

int	load_check_frames(t_data *data)
{
	int	i;

	load_frames(data);
	data->reload_frame_count = 25;
	data->ticks_per_frame = 2;
	i = 0;
	while (i < data->reload_frame_count)
	{
		if (data->reload_frames[i] == NULL)
		{
			printf("Failed to load reload frame %d\n", i);
		}
		i++;
	}
	return (0);
}

static void	draw_texture_block(t_data *data, uint32_t col, int x, int y)
{
	if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
		put_pixel(data, x, y, col);
}

static void	draw_texture(t_data *data, mlx_texture_t *t,
				int dest_x, int dest_y)
{
	uint32_t	*pixels;
	int			sy;
	int			sx;
	uint32_t	col;
	uint8_t		a;

	pixels = (uint32_t *)t->pixels;
	sy = 0;
	while (sy < (int)t->height)
	{
		sx = 0;
		while (sx < (int)t->width)
		{
			col = pixels[sy * t->width + sx];
			a = (col >> 24) & 0xFF;
			if (a != 0)
				draw_texture_block(data, col, dest_x + sx, dest_y + sy);
			sx++;
		}
		sy++;
	}
}

void	draw_reload_overlay(t_data *data)
{
	mlx_texture_t	*t;
	int				dest_x;
	int				dest_y;

	if (data->reload_frame_count <= 0)
		return ;
	t = data->reload_frames[data->reload_current];
	if (t == NULL)
		return ;
	dest_x = MAP_WIDTH - t->width;
	dest_y = MAP_HEIGHT - t->height;
	if (dest_x < 0)
		dest_x = 0;
	if (dest_y < 0)
		dest_y = 0;
	draw_texture(data, t, dest_x, dest_y);
}
