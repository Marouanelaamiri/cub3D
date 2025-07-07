/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/07 15:19:51 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
t_data *g_map = NULL;

void f()
{
	system("leaks cub3D");
}

int main(int argc, char **argv)
{
	//atexit(f);
    t_data *info;

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

    clean_map(info);
    free(info);
    return EXIT_SUCCESS;
}