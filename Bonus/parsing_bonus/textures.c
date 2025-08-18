/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:34:13 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:13:19 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	load_textures(t_data *data)
{
	data->no = mlx_load_png(data->no_texture);
	data->so = mlx_load_png(data->so_texture);
	data->we = mlx_load_png(data->we_texture);
	data->ea = mlx_load_png(data->ea_texture);
	data->door = mlx_load_png("Bonus/textures/reddoor.png");
	if (!data->no || !data->so || !data->we || !data->ea || !data->door)
		return (1);
	return (0);
}
