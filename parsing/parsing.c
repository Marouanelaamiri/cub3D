/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/14 17:56:01 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_arguments(int ac, char **av)
{
    char *ext;

    if (ac != 2)
    {
        write(2, "Error: Invalid number of arguments.\n", 35);
        exit(EXIT_FAILURE);
    }

    ext = ft_strrchr(av[1], '.');
    if (!ext || ft_strcmp(ext, ".cub") != 0)
    {
        write(2,
            "Error: Invalid file extension. Expected a filename ending in .cub\n",
            67);
        exit(EXIT_FAILURE);
    }
}

t_data	*malloc_map(void)
{
	t_data			*map;
	const char		*err_msg;

	err_msg = "Error: Memory allocation failed for map.\n";
	map = malloc(sizeof *map);
	if (!map)
	{
		write(2, err_msg, ft_strlen(err_msg));
		exit(EXIT_FAILURE);
	}
	ft_bzero(map, sizeof *map);
	return (map);
}
t_data *parser_map(int ac, char **av)
{
	t_data *map;

	check_arguments(ac, av);
	map = malloc_map();
	if (!map)
		return (NULL);
	 if (!validate_map_file(av[1], map))
    {
        // on failure, is_valid_map_line either exited already
        // or cleaned up and returned 0.
        clean_map(map);
        free(map);
        return NULL;
    }
	return (map);
}
void	check_map_char(t_data *info, int i, int len)
{
	int	j;
	char	c;

	j = 0;
	while (j < len)
	{
		c = info->map[i][j];
		if (c == ' ')
		{
			j++;
			continue;
		}
		printf("DEBUG: map[%d][%d] = '%c'\n", i, j, c);
		if (!ft_strchr("01NSEW", c))
			print_error("Error: Invalid character in map.\n", info);
		j++;
	}
	check_line_for_player(info, i, len);
}
void	check_line_for_player(t_data *info, int i, int len)
{
	int	j;
	char	c;

	j = 0;
	while (j < len)
	{
		c = info->map[i][j];
		if (c != ' ')
		{
			if (!ft_strchr("01NSEW", c))
				print_error("Error: Invalid character in map.\n", info);
			if (ft_strchr("NSEW", c))
			{
				info->player_count++;
				if (info->player_count > 1 && !info->has_error)
					print_error("Error: Multiple player positions found.\n", info);
				info->player_x = j * TILE_SIZE + TILE_SIZE / 2;
				info->player_y = i * TILE_SIZE + TILE_SIZE / 2;
				info->player_direction = c;
				check_surround(info, i, j, len);
			}
		}
		j++;
	}
}
void check_map_line(t_data *info, char *line)
{
	char *checked;
	char **valid_map;
	char *alloc_error;
	int height;

	alloc_error = "Error: Memory allocation failed for map.\n";
	height = info->map_height;	
	if(info->has_error)
		return;
	checked = trimming_line(line, info);//clean line
	valid_map = malloc(sizeof(char *) * (height + 2));
    if (!valid_map)
    {
        free(checked);
        print_error(alloc_error, info);
        info->has_error = 1;
        return;
	}
	copy_existing_map(info, valid_map);//copy existing map
	valid_map[height] = ft_strdup(checked);//add new line to map
	if(!valid_map[height])
		return (free_malloc(info, checked, valid_map, height));
	valid_map[height + 1] = NULL;//add null terminator
	update_map(info, valid_map, checked);//update map info
	free(checked);//free checked line
}
void map_parsing(t_data *info, int *started, char *line)
{
	info->map_parsed = 1;
	*started = 1;
	check_map_line(info, line);
}

int	validate_map_file(char *path, t_data *info)
{
	int		fd;
	int		start;
	char	*line;
	int		res;
	const char	*open_err = "Error: Could not open file.\n";
	const char	*validate_err = "Error: Map validation failed.\n";

	init_data(info);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		info->has_error = 1;
		write(2, open_err, ft_strlen(open_err));
		return (0);
	}
	start = 0;
	while ((line = get_next_line(fd)) && !info->has_error)
	{
		if (!check_line(line, info, &start))
		{
			free(line);
			close(fd);
			clean_map(info);
			return (0);
		}
		free(line);
	}
	close(fd);
	res = final_check(info);
	if (!res)
	{
		write(2, validate_err, ft_strlen(validate_err));
		return (0);
	}
	return (1);
}

void	check_borders(t_data *info)
{
	char	*wall_err;
	int			rows;
	int			max_len;
	int			i;
	int			row_len;

	if (!info || info->has_error)
		return;
		
	rows    = info->map_height;
	max_len = get_max_line_length(info);
	wall_err = "Error: Map is not surrounded by walls.\n";
	i = 0;
	while (i < max_len)
	{
		if (i < ft_strlen(info->map[0]) &&
		    info->map[0][i] != '1' && info->map[0][i] != ' ')
			print_error(wall_err, info);
		i++;
	}
	i = 0;
	while (i < max_len)
	{
		if (i < ft_strlen(info->map[rows - 1]) &&
		    info->map[rows - 1][i] != '1' &&
		    info->map[rows - 1][i] != ' ')
			print_error(wall_err, info);
		i++;
	}
	printf("DEBUG: Map dimensions: %d x %d\n",
	       info->map_width, info->map_height);
	i = 0;
	while (i < rows)
		printf("  [%s]\n", info->map[i++]);
	i = 0;
	while (i < rows)
	{
		row_len = ft_strlen(info->map[i]);
		/* Left edge */
		if (info->map[i][0] != '1' && info->map[i][0] != ' ')
			print_error(wall_err, info);
		/* Right edge */
		if (row_len > 0 &&
		    info->map[i][row_len - 1] != '1' &&
		    info->map[i][row_len - 1] != ' ')
			print_error(wall_err, info);
		check_map_char(info, i, row_len);
		i++;
	}
}
