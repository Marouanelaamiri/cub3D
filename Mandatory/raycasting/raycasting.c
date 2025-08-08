/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/08 21:37:54 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_colliding(t_data *data, float new_px, float new_py)
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



void ff()
{
	system("leaks cub3D");
}

int	main_raycasting(t_data *data)
{
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
