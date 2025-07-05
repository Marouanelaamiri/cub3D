/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:07:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 15:55:06 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void malloc_error(t_map *info, char *line, char **valid_map, int height)
{
	int i;
	i = 0;
	
	free(line);
	while (i < height)
	{
		if (valid_map[i] != info->map[i])
			free(valid_map[i]);
		i++;
	}
	free(valid_map);
	info->has_error = 1;
	write(2, "Error: Memory allocation failed.\n", 34);
}
char **malloc_new_map(t_map *info, char *checked)
{
	char **valid_map;
	
	valid_map = malloc(sizeof(char *) * (info->map_height + 2));
	if (!valid_map)
	{
		free(checked);
		print_error("Error: Memory allocation failed for map.\n", info);
	}
	return valid_map;
}
