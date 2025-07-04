/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:53:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:20 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_strtrim(char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	start = str;
	while (*start == ' ' || *start == '\t' || *start == '\n')
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 1;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimmed[i] = start[i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

