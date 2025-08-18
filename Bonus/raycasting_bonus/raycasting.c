/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:57:09 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 21:03:58 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int slide_check(t_data *data, float corners[4][2], int i)
{
    int mx;
    int my;
	char tile;
    mx = (int)(corners[i][0] / TILE_SIZE);
    my = (int)(corners[i][1] / TILE_SIZE);
   	if (my < 0 || my >= data->recmap_height
		|| mx < 0 || mx >= (int)ft_strlen(data->map[my]))
		return (1);	
	tile = data->map[my][mx];
	if (tile == '1' || tile == DOOR_CLOSED)
		return (1);
    return (0);
}

int slide_handel(t_data *data, float new_px, float new_py)
{
    float px;
    float py;
    float r;
    int i;

    px = new_px;
    py = new_py ;
    r  = COLLIDE_PAD * TILE_SIZE;
    i = 0;
    float corners[4][2] = {
        { px - r, py - r },
        { px + r, py - r },
        { px - r, py + r },
        { px + r, py + r }
    };
    while (i < 4)
    {
        if (slide_check(data, corners, i))
            return (1);
        i++;
    }
    return (0);
}

int is_colliding(t_data *data, float new_px, float new_py)
{

    int tile_x = (int)(new_px / TILE_SIZE);
    int tile_y = (int)(new_py / TILE_SIZE);
	char tile;
	
    if (tile_y >= 0 && tile_y < data->recmap_height
     && tile_x >= 0 && tile_x < (int)ft_strlen(data->map[tile_y]))
	{
		tile = data->map[tile_y][tile_x];
		if (tile == '1' || tile == DOOR_CLOSED)
			return (1);
	}
    if (slide_handel(data, new_px, new_py))
        return (1);
    return 0;
}

void terminate_program(void *param)
{
    t_data *data = (t_data *)param;
	if (!data)
		return;
	free_graphics_and_textures(data);
    if (data->mlx)
        mlx_terminate(data->mlx);
	free_frames(data);
	clean_map(data);
    if (data && data->algo)
        free(data->algo);
    if (data)
	    free(data);
    exit(EXIT_SUCCESS);
}

void	key_hook(void *param)
{
	t_data		*data;
	float		new_x;
	float		new_y;
	int			changed;

	data = (t_data *)param;
	new_x = 0.0f;
	new_y = 0.0f;
	changed = doors_animatin_hooks(data);
	changed = mouse_handel(data, changed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		terminate_program(param);
	changed = key_w(data, changed, new_x, new_y);
	changed = key_s(data, changed, new_x, new_y);
	changed = key_a(data, changed, new_x, new_y);
	changed = key_d(data, changed, new_x, new_y);
	changed = ft_retate(data, changed);
	mlx_set_mouse_pos(data->mlx, MAP_WIDTH / 2, MAP_HEIGHT / 2);
    data->mouse_x = MAP_WIDTH / 2;
   	data->mouse_y = MAP_HEIGHT / 2;
	if (changed)
		redraw(data);
}

int	main_raycasting(t_data *data)
{
	set_wh_map(data);
	data->mlx = mlx_init(MAP_WIDTH, MAP_HEIGHT, "Cub3D", false);
	if (!data->mlx) 
		return (1);
	mlx_get_mouse_pos(data->mlx, &data->mouse_x, &data->mouse_y);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	if (load_textures(data))
    {
        free_graphics_and_textures(data);
        if (data->mlx)
            mlx_terminate(data->mlx);
        return (1);
    }
	load_check_frames(data);
	init_struct(data);
	init_player(data);
	redraw(data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_close_hook(data->mlx, terminate_program, data);
	mlx_loop(data->mlx);
	return (0);
}
