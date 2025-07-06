/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:07:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/06 21:53:23 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_malloc(t_data *info, char *line, char **valid_map, int height)
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

