/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:53:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 18:24:00 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void clean_texture(t_map *info)
{
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
}
void clean_color(t_map *info)
{
	if (info->c_color)
		free(info->c_color);
	if (info->f_color)
		free(info->f_color);
}
void clean_map_arr(t_map *info)
{
	int i;

	i = 0;
	if (info->map)
	{
		while (i < info->map_height)
		{
			if (info->map[i])
				free(info->map[i]);
			i++;
		}
		free(info->map);
	}
}
void clean_map(t_map *info)
{
	if (!info)
		return;
	clean_texture(info);
	clean_color(info);
	clean_map_arr(info);
	if (info->error_message)
		free(info->error_message);
}
char *trimming_line(char *line, t_map *info)
{
	char *trimmed;
	int i;

	trimmed = ft_strdup(line);
	if (!trimmed)
		print_error("Error: Memory allocation failed.\n", info);
	if (trimmed[ft_strlen(trimmed) - 1] == '\n')
		trimmed[ft_strlen(trimmed) - 1] = '\0';
	i = 0;
	while (trimmed[i])
	{
		if (trimmed[i] == '\t')
			trimmed[i] = ' '; // Replace tabs with spaces
		i++;
	}
	return trimmed;
}
