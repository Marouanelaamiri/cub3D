/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:55 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/01 11:26:09 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int main(int argc, char **argv)
{
    t_parse  parse;

    if (argc != 2)
        exit_error("Error\nUsage: ./cub3d path/to/map.cub");
    init_parse(&parse);
    if (!parse_cubfile(argv[1], &parse))
        exit_error("Error\nFailed to parse .cub file");
    // At this point 'parse' is fully populated and valid

    start_executor(&parse);
    // start_executor() will:
    //  1) initialize MLX and window (mlx_init, mlx_new_window, etc.)
    //  2) load textures (mlx_xpm_file_to_image, mlx_get_data_addr)
    //  3) enter the render loop (raycasting + mlx_loop)
    //  4) clean up (free textures, destroy images, close window)

    free_parse(&parse);
    return (0);
}