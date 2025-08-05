/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:07:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/14 18:14:51 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_malloc(t_data *info, char *line, char **valid_map, int height)
{
	int	i;

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
