/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:35:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 15:04:56 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void check_config(t_map *info)
{
	if (!info->no_texture || !info->so_texture || !info->we_texture || !info->ea_texture)
		print_error("Error: Missing texture configuration.\n", info);
	if (!info->f_color || !info->c_color)
		print_error("Error: Missing floor or ceiling color configuration.\n", info);
}

int check_empty_line(char *line, t_map *info, int *start)
{
	if (*start && ft_strlen(line) <= 1)
	{
		info->has_error = 1;
		write(2, "Error: Empty line found in map.\n", 32);
		return 0; // Empty line found
	}
	return 1; // No empty line found
}
void map_parsing(t_map *info, int *started, char *line)
{
	info->map_parsed = 1;
	*started = 1;
	check_map_line(info, line);
}
int check_line(char *line, t_map *info, int *started)
{
	if (!*started && ft_strlen(line) <= 1)
		return 1;
	if (!info->map_parsed && info->config_count < 6)
	{
		if (!check_id(line, info) && ft_strlen(line) > 1)
			map_parsing(info, started, line);
		return(!info->has_error);
	}
	if (ft_strlen(line) <= 1 || info->map_parsed)
	{
		if (!check_empty_line(line, info, started))
			return 0; // Empty line found
		map_parsing(info, started, line);
		return (!info->has_error);
	}
	return 1; // Valid line
}
int final_check(t_map *info)
{
	check_config(info);
	if (info->player_count != 1)
	{
		print_error("Error: Invalid player count.\n", info);
		return 0; // Invalid player count
	}
	check_borders(info);
	if (info->has_error)
		return 0; // Error occurred during checks
	return 1; // All checks passed
}
	
