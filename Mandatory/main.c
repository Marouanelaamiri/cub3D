/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/23 17:58:04 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	f()
{
	system("leaks  cub3D");
}

int	main(int argc, char **argv)
{
	t_data	*info;
	t_algo	*algo;
	int		ret;

	atexit(f);
	info = parser_map(argc, argv);
	if (!info)
		return (EXIT_FAILURE);
	algo = malloc(sizeof(t_algo));
	if (!algo)
		return (EXIT_FAILURE);
	ft_memset(algo, 0, sizeof(t_algo));
	info->algo = algo;
	pad_map_edges_with_walls(info);
	ret = main_raycasting(info);
	free_graphics_and_textures(info);
	clean_map(info);
	free(info);
	return (ret);
}
