/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:21:33 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 09:39:47 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*haystack1;
	char	*needle1;

	i = 0;
	j = 0;
	haystack1 = (char *) haystack;
	needle1 = (char *) needle;
	if (haystack == NULL && len == 0)
		return (needle1);
	if (needle1[j] == '\0')
		return (haystack1);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return (haystack1 + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
