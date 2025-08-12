/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:10:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/11 19:48:17 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_spaces_with_zero(t_data *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->map_height)
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == ' ')
				info->map[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	pad_line(t_data *info, int i, int target_len)
{
	int		old_len;
	int		j;
	char	*new_line;

	old_len = ft_strlen(info->map[i]);
	if (old_len >= target_len)
		return ;
	new_line = malloc(target_len + 1);
	if (!new_line)
		print_error("Malloc failed\n", info);
	j = 0;
	while (j < old_len)
	{
		new_line[j] = info->map[i][j];
		j++;
	}
	while (j < target_len)
	{
		new_line[j] = ' ';
		j++;
	}
	new_line[target_len] = '\0';
	free(info->map[i]);
	info->map[i] = new_line;
}

void	replace_edge_spaces_with_walls(t_data *info, int max_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < max_len)
	{
		if (info->map[0][j] == ' ')
			info->map[0][j] = '1';
		j++;
	}
	j = 0;
	while (j < max_len)
	{
		if (info->map[info->map_height - 1][j] == ' ')
			info->map[info->map_height - 1][j] = '1';
		j++;
	}
	i = 0;
	while (i < info->map_height)
	{
		if (info->map[i][0] == ' ')
			info->map[i][0] = '1';
		if (info->map[i][max_len - 1] == ' ')
			info->map[i][max_len - 1] = '1';
		i++;
	}
}

void	pad_map_edges_with_walls(t_data *info)
{
	int	max_len;
	int	i;

	max_len = get_max_line_length(info);
	i = 0;
	while (i < info->map_height)
	{
		pad_line(info, i, max_len);
		i++;
	}
	replace_edge_spaces_with_walls(info, max_len);
}
