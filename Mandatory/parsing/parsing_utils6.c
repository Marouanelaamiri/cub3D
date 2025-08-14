/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:07:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/14 21:36:45 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_malloc(t_data *info, char *line, char **valid_map, int height)
{
	int	i;

	i = 0;
	free(line);
	while (i < height)
	{
		if (valid_map[i] != info->map[i])
			free(valid_map[i]);
		i++;
	}
	free(valid_map);
	info->has_error = 1;
	write(2, "Error: Memory allocation failed.\n", 34);
}

char	*trimming_line(char *line, t_data *info)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			print_error("Error: Tab not allowed in map.\n", info);
			return (NULL);
		}
		i++;
	}
	dup = ft_strdup(line);
	if (!dup)
		print_error("Error: Memory allocation failed.\n", info);
	len = ft_strlen(dup);
	if (len > 0 && dup[len - 1] == '\n')
		dup[len - 1] = '\0';
	return (dup);
}

void	color_error_or_exit(char *value, t_data *info, int is_floor)
{
	if (!value || !check_color(value))
	{
		if (is_floor)
			print_error("Invalid floor color.\n", info);
		else
			print_error("Invalid ceiling color.\n", info);
	}
}

int	validate_token(const char *s)
{
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	map_parsing(t_data *info, int *started, char *line)
{
	info->map_parsed = 1;
	*started = 1;
	check_map_line(info, line);
}
