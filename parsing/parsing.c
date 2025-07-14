/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/08 15:10:32 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_arguments(int ac, char **av)
{
    int         len;
    const char *arg_err;
    const char *ext_err;

    arg_err = "Error: Invalid number of arguments.\n";
    ext_err = "Error: Invalid file extension. Expected .cub\n";

    if (ac != 2)
    {
        write(2, arg_err, ft_strlen(arg_err));
        exit(EXIT_FAILURE);
    }

    len = ft_strlen(av[1]);
    if (len < 4 || ft_strcmp(av[1] + len - 4, ".cub") != 0)
    {
        write(2, ext_err, ft_strlen(ext_err));
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
	if (!is_valid_map_line(av[1], map))
		return (NULL);
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
size_t get_max_line_length(t_data *info)
{
	int i;
	size_t max_length;

	i = 0;
	max_length = 0;
	while ( i < info->map_height)
	{
		max_length = ft_getmax(max_length, ft_strlen(info->map[i]));
		i++;
	}
	return max_length;
}
int check_file_lines(int fd, t_data *info, int *start)
{
	char *line;
	
	line = get_next_line(fd);
	while (line != NULL && !info->has_error)
	{
		if (!check_line(line, info, start))
		{
			free(line);
			return 0; // Invalid line
		}
		free(line);
		line = get_next_line(fd);
	}
	return 1; // All lines are valid
}
int check_if_file_open(char *file, t_data *info, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		info->has_error = 1;
		write(2, "Error: Could not open file.\n", 29);
		return 0; // File could not be opened
	}
	return 1; // File opened successfully
}
int is_valid_map_line(char *line, t_data *info)
{
	int fd;
	int start = 0;
	int res;
	
	init_data(info);
	if(!check_if_file_open(line, info, &fd))
		return 0; // File could not be opened
	start = 0;
	if(!check_file_lines(fd, info, &start))
	{
		close(fd);
		clean_map(info);
		return 0; // Invalid line found
	}
	close(fd);
	res = final_check(info);
	if (!res)
	{
		write(2, "Error: Map validation failed.\n", 30);
		return 0; // Map validation failed

	}
	return 1; // Map is valid
}
void	horizontal_check(t_data *info, int len_max)
{
	int i;
	i = 0;
	while (i < len_max)
	{
		if (i < ft_strlen(info->map[0]) && info->map[0][i] != '1' && info->map[0][i] != ' ')
			print_error("Error: Map is not surrounded by walls.\n", info);
		if ( i < ft_strlen(info->map[info->map_height - 1]) && info->map[info->map_height - 1][i] != '1' && info->map[info->map_height - 1][i] != ' ')
			print_error("Error: Map is not surrounded by walls.\n", info);
		i++;
	}
}
void vertical_check(t_data *info, int i, int len)
{
	if (info->map[i][0] != '1' && info->map[i][0] != ' ')
		print_error("Error: Map is not surrounded by walls.\n", info);
	if (len > 0 && info->map[i][len - 1] != '1' && info->map[i][len - 1] != ' ')
		print_error("Error: Map is not surrounded by walls.\n", info);
}
void check_borders(t_data *info)
{
	int i;
	int len_max;
	int len;
	
	len_max = get_max_line_length(info);
	horizontal_check(info, len_max);
	i = 0;
	printf("DEBUG: Map dimensions: %d x %d\n", info->map_width, info->map_height);
	for (int k = 0; k < info->map_height; k++)
    	printf("  [%s]\n", info->map[k]);
	while (i < info->map_height)
	{
		len = ft_strlen(info->map[i]);
		vertical_check(info, i, len);
		check_map_char(info, i, len);
		i++;
	}
}
