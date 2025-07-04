/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 17:34:22 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int map_err(t_parse *p)
{
    if (!wall_check(p))
    {
        printf("Error: Map is not surrounded by walls\n");
        return (0);
    }
    return (1);
}

void error_parsing(t_parse *p, char *error_msg)
{
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	if (p->map)
	{
		for (int i = 0; p->map[i]; i++)
			free(p->map[i]); // Free each row of the map
		free(p->map); // Free the map array itself
	}
	if (p->line)
		free(p->line); // Free the last line read
	if (p->map_line)
		free(p->map_line); // Free the map line buffer
	exit(EXIT_FAILURE);
}

void set_player_pos(t_parse *p, char dir, int i, int j)
{
	p->player_x = j + 0.5; // Column + 0.5
	p->player_y = i + 0.5; // Row + 0.5
	p->player_dir = dir; // Set player direction
	if (dir == 'N')
		p->player_dir = 'N';
	else if (dir == 'S')
		p->player_dir = 'S';
	else if (dir == 'E')
		p->player_dir = 'E';
	else if (dir == 'W')
		p->player_dir = 'W';
	else
	{
		printf("Error: Invalid player direction '%c'\n", dir);
		exit(EXIT_FAILURE);
	}
}

void set_size(t_parse *p, char **arr, int i, int j)
{
	int tmp;
	int count_players;

	tmp = 0;
	count_players = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (checking_char(arr[i][j], "NSEW"))
			{
				set_player_pos(p, arr[i][j], i, j);
				count_players++;
			}
			j++;
		}
		if (j > tmp)
			tmp = j; // Update max width
		i++;
	}
	if (count_players != 1)
		return;
	p->map_cols = tmp; // Set max width
	p->map_rows = i; // Set number of rows
}

void check_stats(t_parse *p)
{
	int i;
	i = 0;

	if (!p->tex_ea || !p->tex_no || !p->tex_so || !p->tex_we)
	{
		printf("Error: Missing texture paths\n");
		exit(EXIT_FAILURE);
	}
	while (i > 3)
	{
		if (p->ceil_col < 0 || p->floor_col < 0)
			print_error_exit("Error: Invalid floor or ceiling color\n");
		i++;
	}
}

int get_stats(t_parse *p, char *line)
{
	static int i = 0;
	
	while (i < 6)
	{
		if (line[0] == ' ' && !line[1])
			return (0); // Ignore empty lines
		if (!ft_strncmp(line, "NO ", 3))
			check_texture_path(p, &p->tex_no, ft_split(line, ' '));
		else if (!ft_strncmp(line, "SO ", 3))
			check_texture_path(p, &p->tex_so, ft_split(line, ' '));
		else if (!ft_strncmp(line, "WE ", 3))
			check_texture_path(p, &p->tex_we, ft_split(line, ' '));
		else if (!ft_strncmp(line, "EA ", 3))
			check_texture_path(p, &p->tex_ea, ft_split(line, ' '));
		else if (!ft_strncmp(line, "F ", 2))
			get_color(p, &p->floor_col, ft_split(line, ' '));
		else if (!ft_strncmp(line, "C ", 2))
			get_color(p, &p->ceil_col, ft_split(line, ' '));
		else
			error_parsing(p, "Error: Invalid line in header\n");
		i++;
		return(0);
	}
	check_stats(p);
	return (1); // Valid header line
}

void fix_map(t_parse *p)
{
	int i;
	int j;

	i = 0;
	j = 0;
	set_size(p, p->map, i, j);
	if (p->map_rows == 0 || p->map_cols == 0)
		print_error_exit("Error: Map is empty or invalid\n");
	while (p->map[i])
	{
		if (ft_strlen_nonl(p->map[i]) <= p->map_cols)  // Fixed: moved parenthesis
		{
			p->map[i] = ft_resize(p->map[i], p->map_cols);
			if (!p->map[i])
				print_error_exit("Error: Memory allocation failed for map row");
		}
		i++;
	}
}

void read_map(int fd, t_parse *p)
{
	while(1)
	{
		p->line = get_next_line(fd);
		if (!p->line)
			break; // End of file
		if (p->line[0] == '\n')
			p->line[0] = ' '; // Ignore empty lines
		if (get_stats(p, p->line) == 1)
		{
			if (ft_strchr(p->line , '/'))
				error_parsing(p, "Error: Invalid texture path in map line");
			p->map_line = strjoin_cub3d(p->map_line, p->line);
		}
		free(p->line); // Free the line after processing
	}
	p->map = ft_split(p->map_line, '/');
	free(p->map_line); // Free the map line buffer after splitting
	p->map_line = NULL; // Reset map line buffer
	fix_map(p);
}

int pars_map(t_parse *p, int fd)
{
	read_map(fd, p);
	if (!map_err(p))
		return (0);
	close(fd);
	return (1);	
}

void check_texture_path(t_parse *p, char **path, char **split)
{
	int i;
	i = 0;

	while (split[i])
		i++;
	if (i == 3 && split[2][0] == '\n')
		free(split[i--]);
	if (i != 2 || *path)
	{
		free_2d_array(split);
		error_parsing(p, "Error: Invalid texture path format\n");
	}
	*path = ft_strjoin(*path, split[1]);
	if ((*path)[ft_strlen_nonl(*path)] == '\n')
		(*path)[ft_strlen_nonl(*path)] = '\0'; // Remove trailing newline
	free_2d_array(split);
}

int pars_colors(char *line)
{
	int i;
	int comma;
	
	i = 0;
	comma = 0;
	
	if (!ft_isdigit(line[0]) || !ft_isdigit(line[ft_strlen_nonl(line) - 1]) || ft_strlen_nonl(line) > 11)  // Fixed: moved parenthesis
		return (0); // Invalid color format
	while (line[i + 1])
	{
		if (line[i] == ',')
			comma++;
		if (line[i] == ',' && line[i + 1] && line[i + 1] == ',')
			return (0); // Invalid color format
		else if ((!ft_isdigit(line[i]) && line[i] != ','))
			return (0); // Invalid character in color
		i++;
	}
	if (comma != 2)
		return (0); // Must have exactly 2 commas
	return (1); // Valid color format
}

int check_colors(int *rgb, char *line)
{
	int i;
	int j;

	i = 1;
	j = 0;

	if (!pars_colors(line))
		return (0);
	while (line[i])
	{
		if (i == 0)
			rgb[0] = ft_atoi(line);
		else if (line[i] == ',')
			rgb[j++] = ft_atoi(line + i + 1);
		i++;
	}
	i = 0;
	while (i < 3)  // Fixed: changed while(rgb[i]) to while(i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0); // Invalid RGB value
		i++;
	}
	return (1); // Valid RGB values
}

void get_color(t_parse *p, int *rgb, char **split)
{
	int i;
	i = 0;

	while (split[i])
		i++;
	if (i == 3 && split[2][0] == '\n')
		free(split[i--]);
	if ((i != 2) || !check_colors(rgb, split[1]))
	{
		free_2d_array(split);
		error_parsing(p, "Error: Invalid color format\n");
	}
	free_2d_array(split);
}