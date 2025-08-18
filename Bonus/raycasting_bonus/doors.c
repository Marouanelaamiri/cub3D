/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:54:56 by aromani           #+#    #+#             */
/*   Updated: 2025/08/18 20:13:28 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	doors_animatin_hooks(t_data *data)
{
	int			r_now;
	int			e_now;
	static int	r_prev = 0;
	static int	e_prev = 0;
	int			changed;

	changed = 0;
	r_now = mlx_is_key_down(data->mlx, MLX_KEY_R);
	if (r_now && !r_prev)
		start_reload(data);
	r_prev = r_now;
	if (update_reload(data))
		changed = 1;
	e_now = mlx_is_key_down(data->mlx, MLX_KEY_SPACE);
	if (e_now && !e_prev)
	{
		toggle_door(data);
		changed = 1;
	}
	e_prev = e_now;
	return (changed);
}
