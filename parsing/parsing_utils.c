/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 13:03:36 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int check_texture_path(char *path)
{
	int fd;
	char *trim_path;

	if (!path || ft_strlen(path) == 0)
		return 0; // Invalid path
	trim_path = ft_strtrim(path, " \t\n\r");
	if (!trim_path || ft_strlen(trim_path) == 0)
	{
		free(trim_path);
		return 0; // Invalid trimmed path
	}
	fd = open(trim_path, O_RDONLY);
	free(trim_path);
	if (fd < 0)
		return 0; // File could not be opened
	close(fd);
	return 1; // Valid texture path	
}
static int check_so_no(char *trimmed, t_map *info)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && !info->no_texture)
	{
		info->no_texture = ft_strtrim(trimmed + 3, " \n" );
		if(!check_texture_path(info->no_texture))
			print_error("Invalid NO texture path", info);
		return 1;
	}
	if (ft_strncmp(trimmed, "SO ", 3) == 0 && !info->so_texture)
	{
		info->so_texture = ft_strtrim(trimmed + 3, " \n" );
		if(!check_texture_path(info->so_texture))
			print_error("Invalid SO texture path", info);
		return 1;
	}
	return 0;
}
static int check_we_ea(char *trimmed, t_map *info)
{
	if (ft_strncmp(trimmed, "WE ", 3) == 0 && !info->we_texture)
	{
		info->we_texture = ft_strtrim(trimmed + 3, " \n" );
		if(!check_texture_path(info->we_texture))
			print_error("Invalid WE texture path", info);
		return 1;
	}
	if (ft_strncmp(trimmed, "EA ", 3) == 0 && !info->ea_texture)
	{
		info->ea_texture = ft_strtrim(trimmed + 3, " \n" );
		if(!check_texture_path(info->ea_texture))
			print_error("Invalid EA texture path", info);
		return 1;
	}
	return 0;
}
int check_floor_ceiling(char *trimmed, t_map *info)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0 && !info->f_color)
	{
		info->f_color = ft_strtrim(trimmed + 2, " \n" );
		if(!check_color(info->f_color))
		{
			info->has_error = 1;
			write(2, "Invalid floor color\n", 20);
			return 0;
		}
		return 1;
	}
	if (ft_strncmp(trimmed, "C ", 2) == 0 && !info->c_color)
	{
		info->c_color = ft_strtrim(trimmed + 2, " \n" );
		if(!check_color(info->c_color))
		{
			info->has_error = 1;
			write(2, "Invalid ceiling color\n", 22);
			return 0;
		}
		return 1;
	}
	return 0;// No match found
}
int check_id(char *line, t_map *info)
{
	char *trim;
	int res;

	if (info->has_error)
		return 0; // If there's already an error, skip further checks
	trim = ft_strtrim(line, " \t\n\r");
	res = 0;

	if (!trim)
		return 0; // Memory allocation failed
	res = check_so_no(trim, info);
	if (!res && !info->has_error)
		res = check_we_ea(trim, info);
	if (!res && !info->has_error)
		res = check_floor_ceiling(trim, info);
	if (!res && !info->has_error)
		info->config_count++;
	free(trim);
	return res;
}
