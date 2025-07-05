/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:35:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 16:45:21 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void check_config(t_map *info)
{
	if (!info->no_texture || !info->so_texture || !info->we_texture || !info->ea_texture)
		print_error("Error: Missing texture configuration.\n", info);
	if (!info->f_color || !info->c_color)
		print_error("Error: Missing floor or ceiling color configuration.\n", info);
}

int check_empty_line(char *line, t_map *info, int *start)
{
    char *trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        print_error("Memory allocation failed during empty‑line check.\n", info);

    // Once map parsing has started, an empty (whitespace‑only) line is fatal
    if (*start && trimmed[0] == '\0')
    {
        free(trimmed);
        print_error("Empty line found in map.\n", info);
    }

    free(trimmed);
    return 1;
}
void map_parsing(t_map *info, int *started, char *line)
{
	info->map_parsed = 1;
	*started = 1;
	check_map_line(info, line);
}
int check_line(char *line, t_map *info, int *started)
{
    char *trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        print_error("Memory allocation failed during line check.\n", info);

    // 1) Skip leading whitespace‑only lines until we hit the first config or map line
    if (!*started && trimmed[0] == '\0')
    {
        free(trimmed);
        return 1;
    }

    // 2) Config section: expect exactly 6 ID lines
    if (!info->map_parsed && info->config_count < 6)
    {
        if (!check_id(line, info) && trimmed[0] != '\0')
            map_parsing(info, started, line);
        free(trimmed);
        return 1;
    }

    // 3) Map section: whitespace‑only lines are now errors; non‑empty lines go into the map
    if (info->map_parsed)
    {
        if (trimmed[0] == '\0')
        {
            free(trimmed);
            print_error("Empty line found in map.\n", info);
        }
        free(trimmed);
        map_parsing(info, started, line);
        return 1;
    }

    // 4) Fallback (shouldn’t really happen): just continue
    free(trimmed);
    return 1;
}
int final_check(t_map *info)
{
	printf("DEBUG: final_check → player_count = %d\n", info->player_count);
	check_config(info);
	check_borders(info);
	if (info->player_count != 1)
	{
		print_error("Error: Invalid player count.\n", info);
		return 0; // Invalid player count
	}
	if (info->has_error)
		return 0; // Error occurred during checks
	return 1; // All checks passed
}
	
