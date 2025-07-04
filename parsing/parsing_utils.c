/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:03:36 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 14:05:39 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void print_error_exit(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
int ft_check_extension(char *av)
{
    int len;

    len = ft_strlen(av);
    if (len < 5) // Need at least "x.cub"
        return (0);
    if (av[len-4] != '.' || 
        av[len-3] != 'c' || 
        av[len-2] != 'u' || 
        av[len-1] != 'b')
        return (0);
    return (1);
}
int ft_check_file(char *av)
{
    int fd;
    int res;
    char temp[1];

    if (!ft_check_extension(av))
    {
        printf("Error: Invalid file extension\n");
        return (0);
    }
    fd = open(av, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: %s\n", strerror(errno));
        return (0);
    }
    res = read(fd, temp, 1);
    close(fd);
    if (res < 0)
    {
        printf("Error: %s\n", strerror(errno));
        return (0);
    }
    return (1);
}
void init_parse(t_parse *p)
{
	p->screen_w = 0;
	p->screen_h = 0;
	p->tex_no = NULL;
	p->tex_so = NULL;
	p->tex_we = NULL;
	p->tex_ea = NULL;
	p->tex_s = NULL;
	p->floor_col = -1;
	p->ceil_col = -1;
	p->map = NULL;
	p->map_rows = 0;
	p->map_cols = 0;
	p->player_x = -1.0;
	p->player_y = -1.0;
	p->player_dir = '\0';
}
int checking_char(char c, char *valid)
{
	int i;
	i = 0;

	while (valid[i])
	{
		if (c == valid[i])
			return (1); // Character is valid
		i++;
	}
	return (0); // Character is not valid
}
int ft_strlen_nonl(char *s)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}
char *ft_resize(char *str, size_t new_size)
{
	char *new_str;
	size_t i;

	if (!str)
		return (NULL);
	new_str = malloc(new_size + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (i < new_size)
	{
		new_str[i] = ' '; // Fill with spaces if new size is larger
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}
char *strjoin_cub3d(char *s1, char *s2)
{
    int size;
    int i;
    char *tmp;
    
    if (!s2)
        return (NULL);
    
    size = (s1 ? ft_strlen_nonl(s1) : 0) + ft_strlen_nonl(s2);
    tmp = malloc(sizeof(char) * (size + 2));
    if (!tmp)
        return (NULL);
    
    i = 0;
    if (s1)
    {
        while (s1[i])
        {
            tmp[i] = s1[i];
            i++;
        }
        free(s1);
    }
    
    while (*s2 && *s2 != '\n')
    {
        tmp[i] = *s2;
        i++;
        s2++;
    }
    
    tmp[i] = '/';
    tmp[i + 1] = '\0';
    return (tmp);
}
void free_2d_array(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}