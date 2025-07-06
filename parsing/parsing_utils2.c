/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:34:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/06 21:17:20 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_error(char *msg,t_data *info)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	if (info)
	{
		clean_map(info);
		free(info);
	}
	exit(1);
}
void check_surround(t_data *info, int i, int j, int len)
{
	if (i > 0 && ( j >= ft_strlen(info->map[i - 1]) || info->map[i - 1][j] == ' '))
		print_error("Error: Map is not surrounded by walls.\n", info);
	if ( i < info->map_height - 1 && ( j >= ft_strlen(info->map[i + 1]) || info->map[i + 1][j] == ' '))
		print_error("Error: Map is not surrounded by walls.\n", info);
	if (j > 0 && info->map[i][j - 1] == ' ')
		print_error("Error: Map is not surrounded by walls.\n", info);
	if (j < len - 1 && info->map[i][j + 1] == ' ')
		print_error("Error: Map is not surrounded by walls.\n", info);
}
int check_comma(char *line)
{
	int i;
	int comma_cnt;
	
	comma_cnt = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] == ',')
		{
			comma_cnt++;
			if (line[i + 1] == ',')
				return 0; // Invalid format
		}
		i++;
	}
	return (comma_cnt == 2);
}
int check_color_format(char *color)
{
	int i;
	int num_count;

	i = 0;
	num_count = 0;
	
	while(color[i] == ' ' || color[i] == '\t')
		i++;
	while (ft_isdigit(color[i]))
	{
		num_count++;
		i++;
	}
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	return (num_count && color[i] == '\0');
}
int check_range_color(char **colors)
{
	int i;
	int rgb[3];

	i = 0;
	while (colors[i] && i < 3)
	{
		if (!check_color_format(colors[i]))
			return 0; // Invalid color format
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return 0; // Color value out of range
		i++;
	}
	colors[i] = NULL; // Ensure the array is null-terminated
	return (i == 3); // Must have exactly 3 color components
}
int check_color(char *color)
{
	char **colors;
	int valid;

	if (!check_comma(color))
		return 0; // Invalid format
	colors = ft_split(color, ',');
	if (!colors)
		return 0; // Memory allocation failed
	valid = check_range_color(colors);
	ft_free_array(colors);
	return valid;
}


void	ft_free_array(char **arr)
{
	int	n;

	n = 0;
	if (!arr)
		return ;
	while (arr[n])
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}
