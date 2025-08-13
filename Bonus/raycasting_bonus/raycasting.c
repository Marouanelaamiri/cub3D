/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/14 00:12:55 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int is_colliding(t_data *data, float new_px, float new_py)
{
    int tile_x = (int)new_px;
    int tile_y = (int)new_py;

    if (tile_y >= 0 && tile_y < data->recmap_height
        && tile_x >= 0 && tile_x < (int)ft_strlen(data->map[tile_y]))
    {
        char tile = data->map[tile_y][tile_x];
        if (tile == '1' || tile == DOOR_CLOSED)
            return 1; // block only walls and fully closed doors
    }

    // corners for padding — ignore half-open doors
    const float px = new_px * TILE_SIZE + TILE_SIZE / 2.0f;
    const float py = new_py * TILE_SIZE + TILE_SIZE / 2.0f;
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
            || mx < 0 || mx >= (int)ft_strlen(data->map[my]))
            return 1;

        char tile = data->map[my][mx];
        if (tile == '1' || tile == DOOR_CLOSED) // still block walls and closed doors
            return 1;

        // half-open doors ignored here
    }
    return 0;
}

void terminate_program(void *param)
{
    t_data *data = (t_data *)param;
    if (data->img)
	{
        mlx_delete_image(data->mlx, data->img);
	}
    if (data->mlx)
	{
        mlx_terminate(data->mlx);
	}
	free_reload_frames_simple(data);
    exit(0);
}

void	key_hook(void *param)
{
	t_data		*data;
	float		new_x;
	float		new_y;
	int			changed;
	int			r_now;
	int			e_now;
	static int	r_prev = 0;
	static int	e_prev = 0;

	data = (t_data *)param;
	new_x = 0.0f;
	new_y = 0.0f;
	changed = 0;

	/* Handle R press (rising edge) to start reload animation */
	r_now = mlx_is_key_down(data->mlx, MLX_KEY_R);
	if (r_now && !r_prev)
		start_reload_simple(data);
	r_prev = r_now;

	/* Update reload animation tick; if frame changed, request redraw */
	if (update_reload_simple(data))
		changed = 1;

	/* Handle E press (rising edge) to toggle door */
	e_now = mlx_is_key_down(data->mlx, MLX_KEY_SPACE);
	if (e_now && !e_prev)
	{
		toggle_door(data);
		changed = 1;
	}
	e_prev = e_now;

	/* ESC to quit */
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		terminate_program(param);

	/* Movement & rotation */
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
		return (1);
	load_reload_frames_simple(data);
	init_struct(data);
	init_player(data);
	redraw(data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_close_hook(data->mlx, terminate_program, data);
	mlx_loop(data->mlx);
	return (0);
}
