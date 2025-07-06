/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/06 21:17:18 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	    // DEBUG: print exactly what we're opening
    fprintf(stderr, "DEBUG: NO path -> \"%s\"\n", trim_path);
	fd = open(trim_path, O_RDONLY);
	free(trim_path);
	if (fd < 0)
		return 0; // File could not be opened
	close(fd);
	return 1; // Valid texture path	
}
int check_so_no(char *trimmed,t_data *info)
{
    if (ft_strncmp(trimmed, "NO ", 3) == 0)
    {
        if (info->no_texture)
            print_error("Duplicate NO texture identifier.\n", info);

        info->no_texture = ft_strtrim(trimmed + 3, " \n\r\t");
        if (!info->no_texture || !check_texture_path(info->no_texture))
            print_error("Invalid NO texture path.\n", info);
        return 1;
    }
    if (ft_strncmp(trimmed, "SO ", 3) == 0)
    {
        if (info->so_texture)
            print_error("Duplicate SO texture identifier.\n", info);

        info->so_texture = ft_strtrim(trimmed + 3, " \n\r\t");
        if (!info->so_texture || !check_texture_path(info->so_texture))
            print_error("Invalid SO texture path.\n", info);
        return 1;
    }
    return 0;
}

int check_we_ea(char *trimmed,t_data *info)
{
    if (ft_strncmp(trimmed, "WE ", 3) == 0)
    {
        if (info->we_texture)
            print_error("Duplicate WE texture identifier.\n", info);

        info->we_texture = ft_strtrim(trimmed + 3, " \n\r\t");
        if (!info->we_texture || !check_texture_path(info->we_texture))
            print_error("Invalid WE texture path.\n", info);
        return 1;
    }
    if (ft_strncmp(trimmed, "EA ", 3) == 0)
    {
        if (info->ea_texture)
            print_error("Duplicate EA texture identifier.\n", info);

        info->ea_texture = ft_strtrim(trimmed + 3, " \n\r\t");
        if (!info->ea_texture || !check_texture_path(info->ea_texture))
            print_error("Invalid EA texture path.\n", info);
        return 1;
    }
    return 0;
}

int check_floor_ceiling(char *trimmed,t_data *info)
{
    if (ft_strncmp(trimmed, "F ", 2) == 0)
    {
        if (info->f_color)
            print_error("Duplicate floor color identifier.\n", info);

        info->f_color = ft_strtrim(trimmed + 2, " \n\r\t");
        if (!info->f_color || !check_color(info->f_color))
            print_error("Invalid floor color.\n", info);
        return 1;
    }
    if (ft_strncmp(trimmed, "C ", 2) == 0)
    {
        if (info->c_color)
            print_error("Duplicate ceiling color identifier.\n", info);

        info->c_color = ft_strtrim(trimmed + 2, " \n\r\t");
        if (!info->c_color || !check_color(info->c_color))
            print_error("Invalid ceiling color.\n", info);
        return 1;
    }
    return 0;
}
int check_id(char *line,t_data *info)
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
