/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:34:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/15 15:25:38 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_surround(t_data *info, int i, int j, int len)
{
	char	**map;
	int		up_len;
	int		down_len;
	char	*err_msg;

	map = info->map;
	err_msg = "Error: Map is not surrounded by walls.\n";
	if (i > 0)
	{
		up_len = ft_strlen(map[i - 1]);
		if (j >= up_len || map[i - 1][j] == ' ')
			print_error(err_msg, info);
	}
	if (i < info->map_height - 1)
	{
		down_len = ft_strlen(map[i + 1]);
		if (j >= down_len || map[i + 1][j] == ' ')
			print_error(err_msg, info);
	}
	if ((j > 0 && map[i][j - 1] == ' ')
		|| (j < len - 1 && map[i][j + 1] == ' '))
		print_error(err_msg, info);
}

int	check_comma(char *line)
{
	int		comma_cnt;
	char	*c;

	if (!line)
		return (0);
	comma_cnt = 0;
	c = line;
	while (*c)
	{
		if (*c == ',')
		{
			comma_cnt++;
			if (*(c + 1) == ',' || comma_cnt > 2)
				return (0);
		}
		c++;
	}
	if (comma_cnt == 2)
		return (1);
	return (0);
}

int	check_c_format(char *color)
{
	char	*p;
	int		digit_count;

	if (!color)
		return (0);
	p = color;
	while (*p == ' ' || *p == '\t')
		p++;
	digit_count = 0;
	while (ft_isdigit(*p))
	{
		digit_count++;
		p++;
	}
	while (*p == ' ' || *p == '\t')
		p++;
	if (digit_count > 0 && *p == '\0')
		return (1);
	return (0);
}

int	check_c_range(char **colors)
{
	int	i;
	int	value;

	if (!colors)
		return (0);
	i = 0;
	while (i < 3 && colors[i])
	{
		if (!check_c_format(colors[i]))
			return (0);
		value = ft_atoi(colors[i]);
		if (value < 0 || value > 255)
			return (0);
		i++;
	}
	if (i == 3)
	{
		colors[3] = NULL;
		return (1);
	}
	return (0);
}

int	check_color(char *color)
{
	char	**colors;
	int		valid;

	if (!check_comma(color))
		return (0);
	colors = ft_split(color, ',');
	if (!colors)
		return (0);
	valid = check_c_range(colors);
	ft_free_array(colors);
	return (valid);
}
