/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:07:38 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/01 21:27:27 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:07:38 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/01 21:20:00 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	color_error_or_exit(char *value, t_data *info, int is_floor)
{
	if (!value || !check_color(value))
	{
		if (is_floor)
			print_error("Invalid floor color.\n", info);
		else
			print_error("Invalid ceiling color.\n", info);
	}
}

int	parse_color(char *str, t_data *info, int is_floor)
{
	char	*value;
	int		r;
	int		g;
	int		b;

	value = ft_strtrim(str, " \n\r\t");
	color_error_or_exit(value, info, is_floor);
	if (sscanf(value, "%d,%d,%d", &r, &g, &b) != 3)
	{
		if (is_floor)
			print_error("Floor color components out of range.\n", info);
		else
			print_error("Ceiling color components out of range.\n", info);
	}
	if (is_floor)
	{
		validate_floor_rgb(r, g, b, info);
		assign_floor_color(info, r, g, b);
	}
	else
	{
		validate_ceiling_rgb(r, g, b, info);
		assign_ceiling_color(info, r, g, b);
	}
	return (free(value), 1);
}
