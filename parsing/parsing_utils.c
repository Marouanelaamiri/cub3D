/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/07 16:42:22 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_texture_path(char *path)
{
    int fd;
    char *trim_path;

    // 1) NULL or empty input?
    if (!path || !*path)
        return 0;

    // 2) Trim whitespace
    trim_path = ft_strtrim(path, " \t\n\r");
    if (!trim_path)           // malloc failed
        return 0;

    // 3) Empty after trim?
    if (!*trim_path)          // same as strlen == 0
    {
        free(trim_path);
        return 0;
    }

    // DEBUG
    fprintf(stderr, "DEBUG: Opening \"%s\"\n", trim_path);

    // 4) Try opening
    fd = open(trim_path, O_RDONLY);
    free(trim_path);

    if (fd < 0)               // couldn’t open
        return 0;
    close(fd);

    // 5) All good
    return 1;
}
// int check_so_no(char *trimmed,t_data *info)
// {
//     if (ft_strncmp(trimmed, "NO ", 3) == 0)
//     {
//         if (info->no_texture)
//             print_error("Duplicate NO texture identifier.\n", info);

//         info->no_texture = ft_strtrim(trimmed + 3, " \n\r\t");
//         if (!info->no_texture || !check_texture_path(info->no_texture))
//             print_error("Invalid NO texture path.\n", info);
//         return 1;
//     }
//     if (ft_strncmp(trimmed, "SO ", 3) == 0)
//     {
//         if (info->so_texture)
//             print_error("Duplicate SO texture identifier.\n", info);

//         info->so_texture = ft_strtrim(trimmed + 3, " \n\r\t");
//         if (!info->so_texture || !check_texture_path(info->so_texture))
//             print_error("Invalid SO texture path.\n", info);
//         return 1;
//     }
//     return 0;
// }

// int check_we_ea(char *trimmed,t_data *info)
// {
//     if (ft_strncmp(trimmed, "WE ", 3) == 0)
//     {
//         if (info->we_texture)
//             print_error("Duplicate WE texture identifier.\n", info);

//         info->we_texture = ft_strtrim(trimmed + 3, " \n\r\t");
//         if (!info->we_texture || !check_texture_path(info->we_texture))
//             print_error("Invalid WE texture path.\n", info);
//         return 1;
//     }
//     if (ft_strncmp(trimmed, "EA ", 3) == 0)
//     {
//         if (info->ea_texture)
//             print_error("Duplicate EA texture identifier.\n", info);

//         info->ea_texture = ft_strtrim(trimmed + 3, " \n\r\t");
//         if (!info->ea_texture || !check_texture_path(info->ea_texture))
//             print_error("Invalid EA texture path.\n", info);
//         return 1;
//     }
//     return 0;
// }

// int check_floor_ceiling(char *trimmed,t_data *info)
// {
//     if (ft_strncmp(trimmed, "F ", 2) == 0)
//     {
//         if (info->f_color)
//             print_error("Duplicate floor color identifier.\n", info);

//         info->f_color = ft_strtrim(trimmed + 2, " \n\r\t");
//         if (!info->f_color || !check_color(info->f_color))
//             print_error("Invalid floor color.\n", info);
//         return 1;
//     }
//     if (ft_strncmp(trimmed, "C ", 2) == 0)
//     {
//         if (info->c_color)
//             print_error("Duplicate ceiling color identifier.\n", info);

//         info->c_color = ft_strtrim(trimmed + 2, " \n\r\t");
//         if (!info->c_color || !check_color(info->c_color))
//             print_error("Invalid ceiling color.\n", info);
//         return 1;
//     }
//     return 0;
// }
// int check_id(char *line,t_data *info)
// {
// 	char *trim;
// 	int res;

// 	if (info->has_error)
// 		return 0; // If there's already an error, skip further checks
// 	trim = ft_strtrim(line, " \t\n\r");
// 	res = 0;

// 	if (!trim)
// 		return 0; // Memory allocation failed
// 	res = check_so_no(trim, info);
// 	if (!res && !info->has_error)
// 		res = check_we_ea(trim, info);
// 	if (!res && !info->has_error)
// 		res = check_floor_ceiling(trim, info);
// 	if (!res && !info->has_error)
// 		info->config_count++;
// 	free(trim);
// 	return res;
// }
int check_id(char *line, t_data *info)
{
    char    *trim;
    char    *value;
    char   **field;
    char    *dup_msg;
    char    *inv_msg;
    int      prefix_len;
    int      is_texture;

    if (info->has_error)
        return 0;

    trim = ft_strtrim(line, " \t\n\r");
    if (!trim)
        return 0;

    if (ft_strncmp(trim, "NO ", 3) == 0)
    {
        prefix_len  = 3;
        field       = &info->no_texture;
        dup_msg     = "Duplicate NO texture identifier.\n";
        inv_msg     = "Invalid NO texture path.\n";
        is_texture  = 1;
    }
    else if (ft_strncmp(trim, "SO ", 3) == 0)
    {
        prefix_len  = 3;
        field       = &info->so_texture;
        dup_msg     = "Duplicate SO texture identifier.\n";
        inv_msg     = "Invalid SO texture path.\n";
        is_texture  = 1;
    }
    else if (ft_strncmp(trim, "WE ", 3) == 0)
    {
        prefix_len  = 3;
        field       = &info->we_texture;
        dup_msg     = "Duplicate WE texture identifier.\n";
        inv_msg     = "Invalid WE texture path.\n";
        is_texture  = 1;
    }
    else if (ft_strncmp(trim, "EA ", 3) == 0)
    {
        prefix_len  = 3;
        field       = &info->ea_texture;
        dup_msg     = "Duplicate EA texture identifier.\n";
        inv_msg     = "Invalid EA texture path.\n";
        is_texture  = 1;
    }
    else if (ft_strncmp(trim, "F ", 2) == 0)
    {
        prefix_len  = 2;
        field       = &info->f_color;
        dup_msg     = "Duplicate floor color identifier.\n";
        inv_msg     = "Invalid floor color.\n";
        is_texture  = 0;
    }
    else if (ft_strncmp(trim, "C ", 2) == 0)
    {
        prefix_len  = 2;
        field       = &info->c_color;
        dup_msg     = "Duplicate ceiling color identifier.\n";
        inv_msg     = "Invalid ceiling color.\n";
        is_texture  = 0;
    }
    else
    {
        free(trim);
        return 0;
    }

    if (*field)
        print_error(dup_msg, info);

    value = ft_strtrim(trim + prefix_len, " \n\r\t");
    if (!value)
        print_error(inv_msg, info);
    else if (is_texture && !check_texture_path(value))
        print_error(inv_msg, info);
    else if (!is_texture && !check_color(value))
        print_error(inv_msg, info);

    *field = value;
    free(trim);
    return 1;
}

