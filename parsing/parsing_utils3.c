/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:35:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/08 16:10:36 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
void check_config(t_data *info)
{
    char    *tex_msg;
    char    *color_msg;

    /* Error messages */
    tex_msg   = "Error: Missing texture configuration.\n";
    color_msg = "Error: Missing floor or ceiling color configuration.\n";

    /* Ensure all four textures are set */
    if (!info->no_texture || !info->so_texture ||
        !info->we_texture || !info->ea_texture)
        print_error(tex_msg, info);

    /* Ensure both floor and ceiling colors are set */
    if (!info->f_color || !info->c_color)
        print_error(color_msg, info);
}

int check_empty_line(char *line, t_data *info, int *start)
{
    char    *trimmed;
    char    *alloc_msg;
    char    *empty_msg;

    /* Error messages */
    alloc_msg = "Memory allocation failed during empty‑line check.\n";
    empty_msg = "Empty line found in map.\n";

    /* Trim whitespace */
    trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        print_error(alloc_msg, info);

    /* If map parsing has begun, an empty line is fatal */
    if (*start && *trimmed == '\0')
    {
        free(trimmed);
        print_error(empty_msg, info);
    }

    free(trimmed);
    return 1;
}

int check_line(char *line, t_data *info, int *started)
{
    char *trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        print_error("Memory allocation failed during line check.\n", info);
    if (!*started && !*trimmed) {
        free(trimmed);
        return 1;
    }
    if (!info->map_parsed && info->config_count < 6) {
        if (!check_id(line, info) && *trimmed)
            map_parsing(info, started, line);
        free(trimmed);
        return 1;
    }
    if (info->map_parsed) {
        if (!*trimmed) {
            free(trimmed);
            print_error("Empty line found in map.\n", info);
        }
        free(trimmed);
        map_parsing(info, started, line);
        return 1;
    }
    free(trimmed);
    return 1;
}

int final_check(t_data *info)
{
    int         pc;
    char *player_err;
    
    player_err = "Error: Invalid player count.\n";
    printf("DEBUG: final_check → player_count = %d\n", info->player_count);
    check_config(info);
    check_borders(info);
    pc = info->player_count;
    if (pc != 1)
    {
        print_error(player_err, info);
        return 0;
    }
    if (info->has_error)
        return 0;
    
    return 1;
}
	
