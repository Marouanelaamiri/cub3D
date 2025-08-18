/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:52:40 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:14:28 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if ((int)count < 0 && (int)size < 0)
		return (NULL);
	tmp = malloc(count * size);
	if (tmp == NULL)
	{
		return (NULL);
	}
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}
