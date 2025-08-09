/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:07:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/09 19:57:42 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_malloc(t_data *info, char *line, char **valid_map, int height)
{
	int	i;

	i = 0;
	free(line);
	while (i < height)
	{
		if (valid_map[i] != info->map[i])
			free(valid_map[i]);
		i++;
	}
	free(valid_map);
	info->has_error = 1;
	write(2, "Error: Memory allocation failed.\n", 34);
}

char	*trimming_line(char *line, t_data *info)
{
	int	i = 0;

	while (line[i])
	{
		if (line[i] == '\t')
		{
			print_error("Error: Tab characters are not allowed in map.\n", info);
			return (NULL);
		}
		i++;
	}

	char *dup = ft_strdup(line);
	if (!dup)
		print_error("Error: Memory allocation failed.\n", info);

	int len = ft_strlen(dup);
	if (len > 0 && dup[len - 1] == '\n')
		dup[len - 1] = '\0';

	return (dup);
}
