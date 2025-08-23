/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:10:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/21 20:05:38 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	replace_spaces_in_row(char *row, int length)
{
	int	j;

	j = 0;
	while (j < length)
	{
		if (row[j] == ' ')
			row[j] = '1';
		j++;
	}
}

void	replace_edge_spaces_with_walls(t_data *info, int max_len)
{
	int	i;

	replace_spaces_in_row(info->map[0], max_len);
	replace_spaces_in_row(info->map[info->map_height - 1], max_len);
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
