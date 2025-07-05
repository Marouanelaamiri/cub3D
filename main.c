/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/05 16:21:02 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int main(int argc, char **argv)
{
    t_map *info;

    // 1) Check args
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 2) Invoke parser_map (will exit(1) on any fatal parse error)
    info = parser_map(argc, argv);

    // 3) If we get here, parsing succeeded
    printf("✅ Parsing succeeded!\n");
    printf(" Map: %d columns × %d rows\n", info->map_width, info->map_height);
    printf(" Player at (%.1f, %.1f) facing '%c'\n",
           info->player_x, info->player_y, info->player_direction);

    // 4) (optional) dump raw map
    for (int y = 0; y < info->map_height; y++)
        printf("  %s\n", info->map[y]);

    clean_map(info);
    free(info);
    return EXIT_SUCCESS;
}