/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 21:45:41 by malaamir         ###   ########.fr       */
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
	map->map = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->so_texture = NULL;
	map->no_texture = NULL;
	map->ea_texture = NULL;
	map->we_texture = NULL;
	map->c_color = -1;
	map->f_color = -1;
	map->has_error = 0;
	map->player_count = 0;
	map->config_count = 0;
	return (map);
}
t_map *parser_map(int ac, char **av)
{
	t_map *map;

	check_arguments(ac, av);
	map = malloc_map();
	if (!map)
		return (NULL);
	if(!valid_map(av[1], map))
	{
		free_map(map);
		return (NULL);
	}
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
			if (!ft_strchr("01NSEW", info->map[i][j]))
				print_error("Error: Invalid character in map.\n", info);
			if (ft_strchr("NSEW", info->map[i][j]))
				check_sroundings(info, i, j,len);
		}
		j++;
	}
}
void check_player_pos(char c, int x, t_map *info, int height)
{
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
		if (ft_strchr("01NSEW", checked[i]))
				check_player_pos(checked[i], i, info, height);
	}
			
}
void check_map_line(t_map *info, char *line)
{
	char *checked;
	char **valid_map;

	if(info->has_error)
		return;
	checked = checked_line(line, info);//clean line
	valid_map = malloc_new_map(checked, info);//allocate new map
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
		check_malloc_failed(checked, info, info->map_height);
		return;
	}
	valid_map[info->map_height + 1] = NULL;//add null terminator
	update_map_info(info, valid_map, checked);//update map info
	check_lines_char(checked, info, info->map_height - 1);//check player position and characters
	free(checked);//free checked line
}
size_t get_max_line_length(char **map) //maybe need change
{
	size_t max_length = 0;
	size_t current_length;
	int i;

	i = 0;
	while (map[i])
	{
		current_length = ft_strlen(map[i]);
		if (current_length > max_length)
			max_length = current_length;
		i++;
	}
	return max_length;
}
static int check_file_lines(int fd, t_map *info, int *start)
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
static int check_if_file_open(char *file, t_map *info, int *fd)
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
		ft_clean_map(info);//todo
		return 0; // Invalid line found
	}
	close(fd);
	res = final_check(info);
	if (!res || info->has_error)
	{
		write(2, "Error: Map validation failed.\n", 31);
		if (info->has_error)
			write(2, info->error_message, ft_strlen(info->error_message));
		ft_clean_map(info);
		return 0; // Final check failed or error occurred
	}
	return 1; // Map is valid
}
void	horizontal_check(t_map*info, int len_max)
{
	int i;
	i = 0;
	while (i < len_max)
	{
		if (i < ft_strlen(info->map[0] && info->map[0][i] != '1' && info->map[0][i] != ' '))
			print_error("Error: Map is not surrounded by walls.\n", info);
		if ( i < ft_strlen(info->map[info->map_height - 1]) && info->map[info->map_height - 1][i] != '1' && info->map[info->map_height - 1][i] != ' ')
			print_error("Error: Map is not surrounded by walls.\n", info);
		i++;
	}
}