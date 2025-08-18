/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:31:28 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 21:56:22 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texters(t_data *data)
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

uint32_t	get_wall_pixel(t_data *data, \
	int wall_height, int wall_top, int screen_y)
{
	uint32_t	*texture_pixels;
	float		tex_ratio;
	int			tex_y;
	int			tex_x;

	texture_pixels = (uint32_t *)data->tex->pixels;
	tex_ratio = (float)(screen_y - wall_top) / wall_height;
	tex_y = (int)(tex_ratio * (data->tex->height - 1));
	tex_y = fmax(0, fmin(data->tex->height - 1, tex_y));
	tex_x = (int)data->tex_x;
	return (texture_pixels[tex_y * data->tex->width + tex_x]);
}

void	draw_wall(t_data *data, int wall_height, \
	int wall_top, int screen_pos[2])
{
	int			screen_x;
	int			screen_y;
	uint32_t	pixel_color;

	screen_x = screen_pos[1];
	screen_y = screen_pos[0];
	pixel_color = get_wall_pixel(data, wall_height, wall_top, screen_y);
	put_pixel(data, screen_x, screen_y, pixel_color);
}

void	free_textures(t_data *data)
{
	if (data->no)
	{
		mlx_delete_texture(data->no);
		data->no = NULL;
	}
	if (data->so)
	{
		mlx_delete_texture(data->so);
		data->so = NULL;
	}
	if (data->we)
	{
		mlx_delete_texture(data->we);
		data->we = NULL;
	}
	if (data->ea)
	{
		mlx_delete_texture(data->ea);
		data->ea = NULL;
	}
	if (data->img)
	{
		mlx_delete_image(data->mlx, data->img);
		data->img = NULL;
	}
}

void	free_graphics_and_textures(t_data *data)
{
	if (!data)
		return ;
	free_textures(data);
}
