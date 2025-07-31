/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/31 21:19:39 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

t_data *g_map = NULL;

void f()
{
	system("leaks cub3D");
}

#include "parser.h"   // now includes load_textures()

int main(int argc, char **argv)
{
    t_data *info;
    int     ret;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
        return EXIT_FAILURE;
    }

    info = parser_map(argc, argv);
    if (!info)
        return EXIT_FAILURE;

    printf("✅ Parsing succeeded!\n");
    printf(" Map: %d columns × %d rows\n", info->map_width, info->map_height);
    printf(" Player at (%.1f, %.1f) facing '%c'\n",
           info->player_x, info->player_y, info->player_direction);
    put_map_2dv(info);
    //main_raycasting(info);

    // ────────────────────────────────
    // New: load all four textures into info->no/so/we/ea
    load_textures(info);
    // ────────────────────────────────

    // Now launch your put_map_2dv (which initializes MLX, does raycasting, enters the loop)
    ret = put_map_2dv(info);

    // Cleanup after window closes
    clean_map(info);
    free(info);
    return (ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
