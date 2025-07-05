/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:08:01 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 14:18:31 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_getmax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void init_map(t_map *info)
{
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->f_color = NULL;
	info->c_color = NULL;
	info->map = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->player_count = 0;
	info->config_count = 0;
	info->map_parsed = 0;
	info->error_message = NULL;
}
void update_map(t_map *info, char **valid_map, char *checked)
{
	free(info->map);
	info->map = valid_map;
	info->map_height++;
	info->map_width = ft_getmax(info->map_width, ft_strlen(checked));
}
void copy_existing_map(t_map *info, char **valid_map)
{
	int i;
}