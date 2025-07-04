/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:05:18 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 14:02:39 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// char	**ft_realloc(char **lines, int line_count, char *new_line)
// {
// 	char	**new_lines;
// 	int		i;

// 	new_lines = malloc(sizeof(char *) * (line_count + 2));
// 	if (!new_lines)
// 		exit_error("Memory allocation failed for lines");
// 	i = 0;
// 	while (i < line_count)
// 	{
// 		new_lines[i] = lines[i];
// 		i++;
// 	}
// 	new_lines[i] = new_line;
// 	new_lines[i + 1] = NULL; 
// 	free(lines); 
// 	return (new_lines);
// }