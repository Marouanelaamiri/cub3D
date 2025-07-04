/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:20:24 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 17:39:44 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int col_check(char **col, int y, int x, int size_y)
{
    if (!col || x < 0 || y < 0 || size_y <= 0)
        return (0);

    // Check top row
    if (!checking_char(col[y][x], "1"))
        return (0);

    // Check bottom row
    if (!checking_char(col[size_y][x], "1"))
        return (0);

    y++; // Start from next row
    while (y < size_y)
    {
        if (!col[y] || x >= (int)ft_strlen(col[y]))
            return (0);

        if (!checking_char(col[y][x], "10NSEW "))
            return (0);

        if (col[y][x] == ' ')
        {
            if (y > 0 && col[y - 1][x] != '1')
                return (0);
            while (y < size_y && col[y][x] == ' ')
                y++;
            if (y < size_y && col[y][x] != '1')
                return (0);
        }
        y++;
    }
    return (1);
}
int check_vertical_walls(t_parse *p, int rows, int cols)
{
    int i;

    i = 0;
    while (i < cols)
    {
        // Start from row 0 and go to last row (rows-1)
        if (!col_check(p->map, 0, i, rows - 1))
            return (0);
        i++;
    }
    return (1);
}
int check_horizontal_walls(t_parse *p, int rows, int cols)
{
    int i;

    i = 0;
    while (i < rows)
    {
        // First column must be '1'
        if (!checking_char(p->map[i][0], "1"))
            return (0);
            
        // Last column must be '1'
        if (!checking_char(p->map[i][cols - 1], "1"))
            return (0);
        i++;
    }
    return (1);
}
int line_check(t_parse *p, char *line, int x)
{
	while (line[x])
	{
		if ((x == 0 && !checking_char(line[x], "1 ")))
			return (0);
		if (!checking_char(line[x], "1NSEW "))
			error_parsing(p, "Error: Invalid character in map\n");
		if (line[x] == ' ')
		{
			if (x > 0 && line[x - 1] != '1')
				return (0);
			while (line[x] == ' ')
				x++;
			if (line[x] != '1' && line[x] != '\0')
				return (0);
		}
		if (line[x])
			x++;
	}
	if (!checking_char(line[x - 1], "1 "))
		return (0);
	return (1);
}
int wall_check(t_parse *p)
{
    int i, j;

    // Check top and bottom walls
    for (j = 0; j < p->map_cols; j++) {
        if (!checking_char(p->map[0][j], "1") || 
            !checking_char(p->map[p->map_rows-1][j], "1")) {
            return (0);
        }
    }

    // Check left and right walls
    for (i = 0; i < p->map_rows; i++) {
        if (!checking_char(p->map[i][0], "1") || 
            !checking_char(p->map[i][p->map_cols-1], "1")) {
            return (0);
        }
    }

    return 1;
}
