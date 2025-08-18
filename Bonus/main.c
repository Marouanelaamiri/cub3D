/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:19:19 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_data	*info;
	t_algo	*algo;
	int		ret;

	algo = malloc(sizeof(t_algo));
	if (argc != 2)
	{
		printf("What the fuck are you doing?\n");
		return (EXIT_FAILURE);
	}
	info = parser_map(argc, argv);
	if (!info)
		return (EXIT_FAILURE);
	ft_memset(algo, 0, sizeof(t_algo));
	info->algo = algo;
	pad_map_edges_with_walls(info);
	patch_holes(info);
	ret = main_raycasting(info);
	free_graphics_and_textures(info);
	clean_map(info);
	free(info);
	return (ret);
}
