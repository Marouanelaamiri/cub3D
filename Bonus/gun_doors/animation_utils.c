/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:20:54 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/14 22:21:29 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_reload(t_data *data)
{
	if (data->reload_frame_count <= 0)
		return ;
	data->reload_playing = 1;
	data->reload_current = 0;
	data->reload_tick = 0;
}

int	update_reload(t_data *data)
{
	if (data->reload_playing == 0)
		return (0);
	data->reload_tick = data->reload_tick + 1;
	if (data->reload_tick >= data->ticks_per_frame)
	{
		data->reload_tick = 0;
		data->reload_current = data->reload_current + 1;
		if (data->reload_current >= data->reload_frame_count)
		{
			data->reload_playing = 0;
			data->reload_current = data->reload_frame_count - 1;
		}
		return (1);
	}
	return (0);
}

void	free_frames(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->reload_frame_count)
	{
		if (data->reload_frames[i] != NULL)
			mlx_delete_texture(data->reload_frames[i]);
		i++;
	}
}
