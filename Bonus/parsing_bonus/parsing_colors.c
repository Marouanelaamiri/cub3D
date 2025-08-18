/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:29:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:12:53 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	convert_tokens(char **tokens, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		while (tokens[i] && tokens[i][0] != '\0'
				&& ft_whitespaces(tokens[i][0]))
			tokens[i]++;
		if (!validate_token(tokens[i]))
			return (0);
		i++;
	}
	*r = ft_atoi(tokens[0]);
	*g = ft_atoi(tokens[1]);
	*b = ft_atoi(tokens[2]);
	return (1);
}

static char	*split_rgb_tokens(char *p, char **tokens)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		tokens[i] = p;
		while (*p && *p != ',')
			p++;
		if (*p == ',')
		{
			*p = '\0';
			p++;
		}
		i++;
	}
	return (p);
}

static int	parse_rgb(const char *value, int *r, int *g, int *b)
{
	char	*dup;
	char	*p;
	char	*tokens[3];

	dup = ft_strdup(value);
	if (!dup)
		return (0);
	p = dup;
	p = split_rgb_tokens(p, tokens);
	if (*p != '\0')
		return (free(dup), 0);
	if (!convert_tokens(tokens, r, g, b))
		return (free(dup), 0);
	return (free(dup), 1);
}

int	parse_color(char *str, t_data *info, int is_floor)
{
	char	*value;
	int		r;
	int		g;
	int		b;

	value = ft_strtrim(str, " \n\r\t");
	color_error_or_exit(value, info, is_floor);
	if (!parse_rgb(value, &r, &g, &b))
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
