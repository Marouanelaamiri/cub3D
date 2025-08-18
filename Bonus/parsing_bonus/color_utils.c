/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:25:22 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:12:35 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	assign_floor_color(t_data *info, int r, int g, int b)
{
	info->f_color = (r << 24) | (g << 16) | (b << 8) | 225;
}

void	assign_ceiling_color(t_data *info, int r, int g, int b)
{
	info->c_color = (r << 24) | (g << 16) | (b << 8) | 255;
}

void	validate_floor_rgb(int r, int g, int b, t_data *info)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_error("Floor color components out of range.\n", info);
}

void	validate_ceiling_rgb(int r, int g, int b, t_data *info)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_error("Ceiling color components out of range.\n", info);
}
