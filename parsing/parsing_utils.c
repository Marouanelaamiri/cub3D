/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/01 21:18:22 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_path(char *path)
{
	int		fd;
	char	*trim_path;
	char	*ext;

	if (!path || !*path)
		return (0);
	trim_path = ft_strtrim(path, " \t\n\r");
	if (!trim_path)
		return (0);
	if (!*trim_path)
	{
		free(trim_path);
		return (0);
	}
	ext = ft_strrchr(trim_path, '.');
	if (!ext || ft_strcmp(ext, ".png") != 0)
		return (free(trim_path), 0);
	fd = open(trim_path, O_RDONLY);
	free(trim_path);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	handle_no_so(char *trim, t_data *info)
{
	char	*value;

	if (ft_strncmp(trim, "NO ", 3) == 0)
	{
		if (info->no_texture)
			print_error("Duplicate NO texture identifier.\n", info);
		value = ft_strtrim(trim + 3, " \n\r\t");
		if (!value || !check_texture_path(value))
			print_error("Invalid NO texture path.\n", info);
		info->no_texture = value;
		return (1);
	}
	if (ft_strncmp(trim, "SO ", 3) == 0)
	{
		if (info->so_texture)
			print_error("Duplicate SO texture identifier.\n", info);
		value = ft_strtrim(trim + 3, " \n\r\t");
		if (!value || !check_texture_path(value))
			print_error("Invalid SO texture path.\n", info);
		info->so_texture = value;
		return (1);
	}
	return (0);
}

static int	handle_we_ea(char *trim, t_data *info)
{
	char	*value;

	if (ft_strncmp(trim, "WE ", 3) == 0)
	{
		if (info->we_texture)
			print_error("Duplicate WE texture identifier.\n", info);
		value = ft_strtrim(trim + 3, " \n\r\t");
		if (!value || !check_texture_path(value))
			print_error("Invalid WE texture path.\n", info);
		info->we_texture = value;
		return (1);
	}
	if (ft_strncmp(trim, "EA ", 3) == 0)
	{
		if (info->ea_texture)
			print_error("Duplicate EA texture identifier.\n", info);
		value = ft_strtrim(trim + 3, " \n\r\t");
		if (!value || !check_texture_path(value))
			print_error("Invalid EA texture path.\n", info);
		info->ea_texture = value;
		return (1);
	}
	return (0);
}

int	check_id(char *line, t_data *info)
{
	char	*trim;
	int		result;

	if (info->has_error)
		return (0);
	trim = ft_strtrim(line, " \t\n\r");
	if (!trim)
		return (0);
	result = handle_no_so(trim, info)
		|| handle_we_ea(trim, info)
		|| handle_fc(trim, info);
	free(trim);
	return (result);
}

int	handle_fc(char *trim, t_data *info)
{
	if (ft_strncmp(trim, "F ", 2) == 0)
		return (parse_color(trim + 2, info, 1));
	if (ft_strncmp(trim, "C ", 2) == 0)
		return (parse_color(trim + 2, info, 0));
	return (0);
}
