/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:33 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/21 20:21:35 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**alloc_valid_map(t_data *info, char *checked)
{
	char		**valid_map;
	char		*error_msg;
	int			height;

	error_msg = "Error: Memory allocation failed for map.\n";
	height = info->map_height;
	valid_map = malloc(sizeof(char *) * (height + 2));
	if (!valid_map)
	{
		free(checked);
		print_error(error_msg, info);
		info->has_error = 1;
		return (NULL);
	}
	return (valid_map);
}

void	check_map_line(t_data *info, char *line)
{
	char		*checked;
	char		**valid_map;
	int			height;

	if (info->has_error)
		return ;
	checked = trimming_line(line, info);
	height = info->map_height;
	valid_map = alloc_valid_map(info, checked);
	if (!valid_map)
		return ;
	copy_existing_map(info, valid_map);
	valid_map[height] = ft_strdup(checked);
	if (!valid_map[height])
	{
		free_malloc(info, checked, valid_map, height);
		return ;
	}
	valid_map[height + 1] = NULL;
	update_map(info, valid_map, checked);
	free(checked);
}

static int	handle_file_open(t_data *info, int fd)
{
	if (fd < 0)
	{
		info->has_error = 1;
		write(2, "Error: Could not open file.\n", 29);
		return (0);
	}
	return (1);
}

static int	read_lines(int fd, t_data *info)
{
	char	*line;
	int		start;

	start = 0;
	line = get_next_line(fd);
	while (line && !info->has_error)
	{
		if (!check_line(line, info, &start))
		{
			free(line);
			close(fd);
			clean_map(info);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	validate_map_file(char *path, t_data *info)
{
	int	fd;
	int	ok;

	init_data(info);
	fd = open(path, O_RDONLY);
	if (!handle_file_open(info, fd))
		return (0);
	ok = read_lines(fd, info);
	close(fd);
	if (!ok)
		return (0);
	if (!final_check(info))
	{
		write(2, "Error: Map validation failed.\n", 30);
		return (0);
	}
	return (1);
}
