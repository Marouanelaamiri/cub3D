/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 21:54:36 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	terminate_program(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	free_graphics_and_textures(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
	clean_map(data);
	free(data->algo);
	free(data);
	exit(EXIT_SUCCESS);
}

void	key_hook(void *param)
{
	t_data	*data;
	float	new_x;
	float	new_y;
	int		changed;

	new_x = 0.0;
	new_y = 0.0;
	changed = 0;
	data = (t_data *)param;
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

int	main_raycasting(t_data *data)
{
	set_wh_map(data);
	data->mlx = mlx_init(MAP_WIDTH, MAP_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (1);
	if (load_textures(data))
	{
		free_graphics_and_textures(data);
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (1);
	}
	init_struct(data);
	init_player(data);
	redraw(data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_close_hook(data->mlx, terminate_program, data);
	mlx_loop(data->mlx);
	return (0);
}
