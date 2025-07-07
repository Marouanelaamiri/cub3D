/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:34:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/07 22:25:39 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_error(char *msg, t_data *info)
{
    const char  *prefix;
    int          prefix_len;
    int          msg_len;

    prefix     = "Error: ";
    prefix_len = ft_strlen(prefix);
    msg_len    = ft_strlen(msg);
    write(2, prefix, prefix_len);
    write(2, msg, msg_len);
    if (info)
    {
        clean_map(info);
        free(info);
    }
    exit(EXIT_FAILURE);
}
void check_surround(t_data *info, int i, int j, int len)
{
    char        **map;
    int			up_len;
    int			down_len;
    char  		*err_msg;

    map     = info->map;
    err_msg = "Error: Map is not surrounded by walls.\n";
    if (i > 0)
    {
        up_len = ft_strlen(map[i - 1]);
        if (j >= up_len || map[i - 1][j] == ' ')
            print_error(err_msg, info);
    }
    if (i < info->map_height - 1)
    {
        down_len = ft_strlen(map[i + 1]);
        if (j >= down_len || map[i + 1][j] == ' ')
            print_error(err_msg, info);
    }
    if (j > 0 && map[i][j - 1] == ' ')
        print_error(err_msg, info);
    if (j < len - 1 && map[i][j + 1] == ' ')
        print_error(err_msg, info);
}

int check_comma(char *line)
{
    int     comma_cnt;
    char   *c;

    if (!line)
        return 0;
    comma_cnt = 0;
    c = line;
    while (*c)
    {
        if (*c == ',')
        {
            comma_cnt++;
            /* Reject adjacent commas or too many commas */
            if (*(c + 1) == ',' || comma_cnt > 2)
                return 0;
        }
        c++;
    }
    /* Exactly two commas → valid */
    if (comma_cnt == 2)
        return 1;
    return 0;
}

int check_c_format(char *color)
{
    char    *p;
    int      digit_count;

    if (!color)
        return 0;

    p = color;
    while (*p == ' ' || *p == '\t')
        p++;

    digit_count = 0;
    while (ft_isdigit(*p))
    {
        digit_count++;
        p++;
    }
    while (*p == ' ' || *p == '\t')
        p++;
    if (digit_count > 0 && *p == '\0')
        return 1;
    return 0;
}

int check_c_range(char **colors)
{
    int i;
    int value;

    if (!colors)
        return 0;

    i = 0;
    while (i < 3 && colors[i])
    {
        if (!check_c_format(colors[i]))
            return 0;
        value = ft_atoi(colors[i]);
        if (value < 0 || value > 255)
            return 0;

        i++;
    }
    if (i == 3)
    {
        colors[3] = NULL;
        return 1;
    }
    return 0;
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
	valid = check_c_range(colors);
	ft_free_array(colors);
	return valid;
}
