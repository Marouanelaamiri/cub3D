/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:13:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/17 18:12:42 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
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
	patch_holes(info);
	ret = main_raycasting(info);
	clean_map(info);
	free(info);
	return (ret);
}
