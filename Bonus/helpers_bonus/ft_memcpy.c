/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:10 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/18 20:15:27 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	unsigned const char	*tmp_src;
	size_t				i;

	if (src == NULL && dst == NULL)
	{
		return (dst);
	}
	i = 0;
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned const char *)src;
	while (n > 0)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
		n--;
	}
	return (dst);
}
