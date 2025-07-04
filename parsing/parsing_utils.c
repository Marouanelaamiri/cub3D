/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 21:53:02 by malaamir         ###   ########.fr       */
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
		
	}
}