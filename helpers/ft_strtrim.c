/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:53:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/14 18:13:32 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
