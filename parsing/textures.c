/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:34:13 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/17 18:48:15 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_textures(t_data *info)
{
    if (info->no_texture)
    {
        info->no = mlx_load_png(info->no_texture);
        if (!info->no)
            print_error("Failed to load north texture\n", info);
    }
    if (info->so_texture)
    {
        info->so = mlx_load_png(info->so_texture);
        if (!info->so)
            print_error("Failed to load south texture\n", info);
    }
    if (info->we_texture)
    {
        info->we = mlx_load_png(info->we_texture);
        if (!info->we)
            print_error("Failed to load west texture\n", info);
    }
    if (info->ea_texture)
    {
        info->ea = mlx_load_png(info->ea_texture);
        if (!info->ea)
            print_error("Failed to load east texture\n", info);
    }
}