/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:55 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 14:00:44 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void print_parse_results(t_parse *p)
{
    printf("=== Parsing Results ===\n");
    printf("Textures:\n");
    printf("NO: %s\n", p->tex_no ? p->tex_no : "NULL");
    printf("SO: %s\n", p->tex_so ? p->tex_so : "NULL");
    printf("WE: %s\n", p->tex_we ? p->tex_we : "NULL");
    printf("EA: %s\n", p->tex_ea ? p->tex_ea : "NULL");
    printf("Colors:\n");
    printf("Floor: %d\n", p->floor_col);
    printf("Ceiling: %d\n", p->ceil_col);
    
    printf("\nMap (%dx%d):\n", p->map_rows, p->map_cols);
    if (p->map)
    {
        for (int i = 0; p->map[i]; i++)
            printf("%s\n", p->map[i]);
    }
    else
    {
        printf("NULL\n");
    }
    
    printf("\nPlayer Position: (%.1f, %.1f)\n", p->player_x, p->player_y);
    printf("Player Direction: %c\n", p->player_dir);
}

int main(int argc, char **argv)
{
    t_parse parse;
    int fd;

    if (argc != 2)
    {
        printf("Usage: %s <map_file.cub>\n", argv[0]);
        return (1);
    }

    init_parse(&parse);
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return (1);
    }

    if (!pars_map(&parse, fd))
    {
        printf("Error during parsing\n");
        close(fd);
        return (1);
    }

    print_parse_results(&parse);

    // Clean up
    if (parse.tex_no) free(parse.tex_no);
    if (parse.tex_so) free(parse.tex_so);
    if (parse.tex_we) free(parse.tex_we);
    if (parse.tex_ea) free(parse.tex_ea);
    if (parse.map)
    {
        for (int i = 0; parse.map[i]; i++)
            free(parse.map[i]);
        free(parse.map);
    }

    return (0);
}