/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:52 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/17 18:07:55 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_top_and_bottom(t_data *info, int max_len)
{
	char	*err;
	int		i;
	char	ch;

	err = "Error: Map is not surrounded by walls.\n";
	i = 0;
	while (i < max_len)
	{
		if (i < ft_strlen(info->map[0]))
		{
			ch = info->map[0][i];
			if (ch != '1' && ch != ' ' && ch != DOOR_CLOSED)
				print_error(err, info);
		}
		if (i < ft_strlen(info->map[info->map_height - 1]))
		{
			ch = info->map[info->map_height - 1][i];
			if (ch != '1' && ch != ' ' && ch != DOOR_CLOSED)
				print_error(err, info);
		}
		i++;
	}
}

static void	check_sides_and_chars(t_data *info)
{
	int		i;
	int		len;
	char	*err;
	char	ch;

	i = 0;
	err = "Error: Map is not surrounded by walls.\n";
	while (i < info->map_height)
	{
		len = ft_strlen(info->map[i]);
		ch = info->map[i][0];
		if (ch != '1' && ch != ' ' && ch != DOOR_CLOSED)
			print_error(err, info);
		if (len > 0)
		{
			ch = info->map[i][len - 1];
			if (ch != '1' && ch != ' ' && ch != DOOR_CLOSED)
				print_error(err, info);
		}
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

void	check_map_char(t_data *info, int i, int len)
{
	int		j;
	char	c;

	j = 0;
	while (j < len)
	{
		c = info->map[i][j];
		if (c == ' ')
		{
			j++;
			continue ;
		}
		if (!ft_strchr("01NSEWD", c))
			print_error("Error: Invalid character in map.\n", info);
		j++;
	}
	check_line_for_player(info, i, len);
}
