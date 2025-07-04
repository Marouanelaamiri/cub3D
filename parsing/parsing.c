/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 19:33:12 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void check_arguments(int ac, char **av)
{
	int len;
	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments.\n", 35);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strcmp(av[1] + len - 4, ".cub") != 0)
	{
		write(2, "Error: Invalid file extension. Expected .cub\n", 45);
		exit(EXIT_FAILURE);
	}
}
