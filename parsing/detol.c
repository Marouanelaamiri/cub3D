/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:53:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/14 18:17:59 by malaamir         ###   ########.fr       */
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
	if (info->c_color)
		free(info->c_color);
	if (info->f_color)
		free(info->f_color);
	clean_map_arr(info);
	if (info->error_message)
		free(info->error_message);
}

char	*trimming_line(char *line, t_data *info)
{
	char	*trimmed;
	int		i;

	trimmed = ft_strdup(line);
	if (!trimmed)
		print_error("Error: Memory allocation failed.\n", info);
	if (trimmed[ft_strlen(trimmed) - 1] == '\n')
		trimmed[ft_strlen(trimmed) - 1] = '\0';
	i = 0;
	while (trimmed[i])
	{
		if (trimmed[i] == '\t')
			trimmed[i] = ' ';
		i++;
	}
	return (trimmed);
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
