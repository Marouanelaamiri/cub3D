/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:52 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/11 15:50:02 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_top_and_bottom(t_data *info, int max_len)
{
	char	*err;
	int		i;

	err = "Error: Map is not surrounded by walls.\n";
	i = 0;
	while (i < max_len)
	{
		if (i < ft_strlen(info->map[0])
			&& info->map[0][i] != '1'
			&& info->map[0][i] != ' ')
			print_error(err, info);
		if (i < ft_strlen(info->map[info->map_height - 1])
			&& info->map[info->map_height - 1][i] != '1'
			&& info->map[info->map_height - 1][i] != ' ')
			print_error(err, info);
		i++;
	}
}

static void	check_sides_and_chars(t_data *info)
{
	int		i;
	int		len;
	char	*err;

	i = 0;
	err = "Error: Map is not surrounded by walls.\n";
	while (i < info->map_height)
	{
		len = ft_strlen(info->map[i]);
		if (info->map[i][0] != '1' && info->map[i][0] != ' ')
			print_error(err, info);
		if (len > 0 && info->map[i][len - 1] != '1'
			&& info->map[i][len - 1] != ' ')
			print_error(err, info);
		check_map_char(info, i, len);
		i++;
	}
}

void	check_borders(t_data *info)
{
	int	max_len;

	if (!info || info->has_error)
		return ;
	max_len = get_max_line_length(info);
	check_top_and_bottom(info, max_len);
	check_sides_and_chars(info);
}

void	map_parsing(t_data *info, int *started, char *line)
{
	info->map_parsed = 1;
	*started = 1;
	check_map_line(info, line);
}
