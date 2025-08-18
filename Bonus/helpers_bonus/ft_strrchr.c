/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:55:46 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:16:05 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	ch;
	char	*ret;

	ch = (char) c;
	i = 0;
	ret = NULL;
	while (s[i])
	{
		if (s[i] == ch)
			ret = (char *) &s[i];
		i++;
	}
	if (ch == '\0')
		return ((char *) &s[i]);
	else
		return (ret);
}
