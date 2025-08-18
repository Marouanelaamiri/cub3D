/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:53:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:16:07 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strtrim(char *str, char *set)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!str || !set)
		return (NULL);
	start = str;
	while (*start && ft_strchr(set, *start))
		start++;
	end = str + ft_strlen(str) - 1;
	while (end > start && ft_strchr(set, *end))
		end--;
	len = end - start + 1;
	return (ft_substr(start, 0, len));
}
