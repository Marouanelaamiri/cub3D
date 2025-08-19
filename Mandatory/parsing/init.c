/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:29:20 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/19 21:38:31 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *info)
{
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->f_color = UINT32_MAX;
	info->c_color = UINT32_MAX;
	info->map = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->player_count = 0;
	info->config_count = 0;
	info->map_parsed = 0;
	info->has_error = 0;
	info->player_x = 0.0f;
	info->player_y = 0.0f;
	info->player_direction = '\0';
}

void	update_map(t_data *info, char **valid_map, char *checked)
{
	free(info->map);
	info->map = valid_map;
	info->map_height++;
	info->map_width = ft_getmax(info->map_width, ft_strlen(checked));
}

void	copy_existing_map(t_data *info, char **valid_map)
{
	int	i;

	i = 0;
	while (i < info->map_height)
	{
		valid_map[i] = info->map[i];
		i++;
	}
}

void	print_error(char *msg, t_data *info)
{
	const char	*prefix;
	int			prefix_len;
	int			msg_len;

	prefix = "Error: ";
	prefix_len = ft_strlen(prefix);
	msg_len = ft_strlen(msg);
	write(2, prefix, prefix_len);
	write(2, msg, msg_len);
	if (info)
	{
		clean_map(info);
		free(info);
	}
	exit(EXIT_FAILURE);
}
