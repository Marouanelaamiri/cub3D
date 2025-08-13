/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/13 20:52:48 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_arguments(int ac, char **av)
{
	char	*ext;

	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments.\n", 37);
		exit(EXIT_FAILURE);
	}
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
	{
		write(2, "Error: Invalid file extension. Expcting .cub\n", 46);
		exit(EXIT_FAILURE);
	}
}

t_data	*malloc_map(void)
{
	t_data			*map;
	const char		*err_msg;

	err_msg = "Error: Memory allocation failed for map.\n";
	map = malloc(sizeof (*map));
	if (!map)
	{
		write(2, err_msg, ft_strlen(err_msg));
		exit(EXIT_FAILURE);
	}
	ft_bzero(map, sizeof (*map));
	return (map);
}

t_data	*parser_map(int ac, char **av)
{
	t_data	*map;

	check_arguments(ac, av);
	map = malloc_map();
	if (!map)
		return (NULL);
	if (!validate_map_file(av[1], map))
	{
		clean_map(map);
		free(map);
		return (NULL);
	}
	return (map);
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
		if (!ft_strchr("01NSEWDd", c))
			print_error("Error: Invalid character in map.\n", info);
		j++;
	}
	check_line_for_player(info, i, len);
}

void	check_line_for_player(t_data *info, int i, int len)
{
	int		j;
	char	c;

	j = 0;
	while (j < len)
	{
		c = info->map[i][j];
		if (c != ' ')
		{
			if (!ft_strchr("01NSEWDd", c))
				print_error("Error: Invalid character in map.\n", info);
			if (ft_strchr("NSEW", c))
			{
				info->player_count++;
				if (info->player_count > 1
					&& !info->has_error)
					print_error("Error: Multiple player pos found.\n", info);
				info->player_x = j * TILE_SIZE + TILE_SIZE / 2;
				info->player_y = i * TILE_SIZE + TILE_SIZE / 2;
				info->player_direction = c;
				check_surround(info, i, j, len);
			}
		}
		j++;
	}
}
