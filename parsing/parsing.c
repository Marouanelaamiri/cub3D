/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 16:46:02 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void check_arguments(int ac, char **av)
{
	int len;
	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments.\n", 35);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strcmp(av[1] + len - 4, ".cub") != 0)
	{
		write(2, "Error: Invalid file extension. Expected .cub\n", 45);
		exit(EXIT_FAILURE);
	}
}
t_map	*malloc_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		write(2, "Error: Memory allocation failed for map.\n", 41);
		exit(EXIT_FAILURE);
	}
	map->no_texture       = NULL;
    map->so_texture       = NULL;
    map->we_texture       = NULL;
    map->ea_texture       = NULL;
    map->f_color          = NULL;
    map->c_color          = NULL;
    map->map              = NULL;
    map->map_height       = 0;
    map->map_width        = 0;
    map->player_count     = 0;
    map->config_count     = 0;

    map->has_error        = 0;          // <— initialize here
    map->player_x         = 0.0f;       // <— initialize here
    map->player_y         = 0.0f;       // <— initialize here
    map->player_direction = '\0';       // <— initialize here

    map->error_message    = NULL;
	return (map);
}
t_map *parser_map(int ac, char **av)
{
	t_map *map;

	check_arguments(ac, av);
	map = malloc_map();
	if (!map)
		return (NULL);
	if (!is_valid_map_line(av[1], map))
		return (NULL);
	return (map);
}
void check_map_char(t_map *info, int i, int len)
{
	int j;
	j = 0;

	while(j < len)
	{
		if (info->map[i][j] != ' ')
		{
			printf("DEBUG: map[%d][%d] = '%c'\n", i, j, info->map[i][j]);
			if (!ft_strchr("01NSEW", info->map[i][j]))
				print_error("Error: Invalid character in map.\n", info);
			if (ft_strchr("NSEW", info->map[i][j]))
			{
				check_player_pos(info->map[i][j], j, info, i);
				check_surround(info, i, j,len);
			}
		}
		j++;
	}
}
void check_player_pos(char c, int x, t_map *info, int height)
{
	printf("DEBUG: Found player '%c' at (%d, %d)\n", c, x, height);
	info->player_count++;
	if( info->player_count > 1 && !info->has_error)
	{
		info->has_error = 1;
		write(2, "Error: Multiple player positions found.\n", 41);
		return;
	}
	info->player_x = x * TILE_SIZE + TILE_SIZE / 2;
	info->player_y = height * TILE_SIZE + TILE_SIZE / 2;
	info->player_direction = c;
}
void check_lines_char(char *checked, t_map *info, int height)
{
	int i;
	i = -1;

	while(checked[++i] && !info->has_error)
	{
		if (ft_strchr("NSEW", checked[i]))
				check_player_pos(checked[i], i, info, height);
	}
			
}
void check_map_line(t_map *info, char *line)
{
	char *checked;
	char **valid_map;

	if(info->has_error)
		return;
	checked = trimming_line(line, info);//clean line
	valid_map = malloc_new_map(info, checked);//allocate new map
	if (!valid_map)
	{
		free(checked);
		info->has_error = 1;
		return;
	}
	copy_existing_map(info, valid_map);//copy existing map
	valid_map[info->map_height] = ft_strdup(checked);//add new line to map
	if(!valid_map[info->map_height])
	{
		malloc_error(info, checked, valid_map, info->map_height);
		return;
	}
	valid_map[info->map_height + 1] = NULL;//add null terminator
	update_map(info, valid_map, checked);//update map info
	// check_lines_char(checked, info, info->map_height - 1);//check player position and characters
	free(checked);//free checked line
}
size_t get_max_line_length(t_map *info)
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
int check_file_lines(int fd, t_map *info, int *start)
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
int check_if_file_open(char *file, t_map *info, int *fd)
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
int is_valid_map_line(char *line, t_map *info)
{
	int fd;
	int start = 0;
	int res;
	
	init_map(info);
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
void	horizontal_check(t_map *info, int len_max)
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
void vertical_check(t_map *info, int i, int len)
{
	if (info->map[i][0] != '1' && info->map[i][0] != ' ')
		print_error("Error: Map is not surrounded by walls.\n", info);
	if (len > 0 && info->map[i][len - 1] != '1' && info->map[i][len - 1] != ' ')
		print_error("Error: Map is not surrounded by walls.\n", info);
}
void check_borders(t_map *info)
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
