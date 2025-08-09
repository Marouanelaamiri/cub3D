/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:53:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/09 19:34:47 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_map_arr(t_data *info)
{
	int	i;

	i = 0;
	if (info->map)
	{
		while (i < info->map_height)
		{
			if (info->map[i])
				free(info->map[i]);
			i++;
		}
		free(info->map);
	}
}

void	clean_map(t_data *info)
{
	if (!info)
		return ;
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
	clean_map_arr(info);
}

void	ft_free_array(char **arr)
{
	int	n;

	n = 0;
	if (!arr)
		return ;
	while (arr[n])
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}
