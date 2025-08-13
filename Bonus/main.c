/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/13 21:17:17 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void f()
// {
// 	system("leaks cub3D");
// }
int	main(int argc, char **argv)
{
	// atexit(f);
	t_data	*info;
	t_algo	*algo;
	int		ret;

	algo = malloc(sizeof(t_algo));
	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	info = parser_map(argc, argv);
	if (!info)
		return (EXIT_FAILURE);
	ft_memset(algo, 0, sizeof(t_algo));
	info->algo = algo;
	pad_map_edges_with_walls(info);
	replace_spaces_with_zero(info);
	debug_print_map(info);// need to be removed
	ret = main_raycasting(info);
	clean_map(info);
	free(info);
	return (ret);
}
