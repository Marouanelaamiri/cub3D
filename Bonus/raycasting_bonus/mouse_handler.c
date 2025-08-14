/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:45:52 by aromani           #+#    #+#             */
/*   Updated: 2025/08/14 18:04:01 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int retate(t_data *data, int32_t m_x, int changed)
{
    if (m_x < data->mouse_x)
    {
        data->ray_angle -= 0.05f;
        if (data->ray_angle < 0)
            data->ray_angle += 2 * M_PI;
        changed = 1;
    }
    else if (m_x > data->mouse_x)
    {
        data->ray_angle += 0.05f;
        if (data->ray_angle >= 2 * M_PI)
            data->ray_angle -= 2 * M_PI;
        changed = 1;
    }
    return (changed);
}

int mouse_handel(t_data *data, int flag)
{
    int32_t m_x; 
    int32_t m_y;
    int changed = 0;
    
    mlx_get_mouse_pos(data->mlx, &m_x, &m_y);
    if (m_x != data->mouse_x || m_y != data->mouse_y)
        changed = retate(data, m_x, changed);
    data->mouse_x = m_x;
    data->mouse_y = m_y;
    if (flag == 1)
        return (1);
    return (changed);
}
	