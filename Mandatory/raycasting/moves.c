/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:40:14 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 21:45:44 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_retate(t_data *data, int flag)
{
	int	changed;

	changed = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->ray_angle -= 0.05f;
		if (data->ray_angle < 0)
			data->ray_angle += 2 * M_PI;
		changed = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->ray_angle += 0.05f;
		if (data->ray_angle >= 2 * M_PI)
			data->ray_angle -= 2 * M_PI;
		changed = 1;
	}
	if (flag == 1)
		return (1);
	return (changed);
}

int	key_w(t_data *data, int flag, float new_x, float new_y)
{
	int	changed;

	changed = 0;
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
	if (flag == 1)
		return (1);
	return (changed);
}

int	key_s(t_data *data, int flag, float new_x, float new_y)
{
	int	changed;

	changed = 0;
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
	if (flag == 1)
		return (1);
	return (changed);
}

int	key_a(t_data *data, int flag, float new_x, float new_y)
{
	int	changed;

	changed = 0;
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
	if (flag == 1)
		return (1);
	return (changed);
}

int	key_d(t_data *data, int flag, float new_x, float new_y)
{
	int	changed;

	changed = 0;
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
	if (flag == 1)
		return (1);
	return (changed);
}
