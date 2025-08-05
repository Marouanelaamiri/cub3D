/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:34:13 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/01 20:17:56 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_data *data)
{
	data->no = mlx_load_png(data->no_texture);
	data->so = mlx_load_png(data->so_texture);
	data->we = mlx_load_png(data->we_texture);
	data->ea = mlx_load_png(data->ea_texture);
	if (!data->no || !data->so || !data->we || !data->ea)
		return (1);
	return (0);
}
