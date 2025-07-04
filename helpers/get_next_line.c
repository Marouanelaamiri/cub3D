/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:28:24 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 17:50:26 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	buffer_pos = 0;
	static int	buffer_len = 0;
	char		*result;
	int			len;

	result = malloc(BUFFER_SIZE + 1);
	if (!result)
		return (-1);
	len = 0;
	while (1)
	{
		if (buffer_pos >= buffer_len)
		{
			buffer_len = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_len <= 0)
				break ;
		}
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break ;
		}
		result[len++] = buffer[buffer_pos++];
		if (len >= BUFFER_SIZE)
			result = realloc_string(result, len, len * 2);
	}
	result[len] = '\0';
	*line = result;
	return (len > 0 || buffer_len > 0) ? 1 : 0;
}