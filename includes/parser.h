/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 21:49:33 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define BUFFER_SIZE 1024
# define MAX_LINE_LENGTH 1024
# define MAX_MAP_SIZE 100

# define TILE_SIZE			40 // should be able to be split by 2
# define MINMP_SIZE			2
# define WIDTH				1920 // 2600
# define HEIGHT				1080 // 1400
# define SCR_WIDTH			5120
# define SCR_HEIGHT			2880
# define HTBOX				0
# define FOV				60
# define WALL_STRIP_WIDTH 	1
# define NUM_RAYS  5120
typedef struct s_map
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	char *f_color;
	char *c_color;
	char **map;
	int map_width;
	int map_height;
	int player_count;
	int config_count;
	int map_parsed;
	float player_x;
	float player_y;
	char	player_direction;
	int has_error;
	char *error_message;
}	t_map;


//============================================================//
int		ft_whitespaces(int c);
int		ft_atoi(const char *str);
void 	ft_bzero(void *s, size_t n);
void 	*ft_calloc(size_t count, size_t size);
int 	ft_isalnum(int c);
int 	ft_isalpha(int c);
int 	ft_isdigit(int c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char *str, char *set);
char	*ft_substr(const char *s, int start, int len);
int 	get_next_line(int fd);
char	*ft_joinfree(char *buffer, char *new_buffer);
char	*get_remaning(char *buffer);
char	*ft_getline(char *buffer);
char	*read_from_file(int fd, char *buffer);
char	**ft_realloc(char **lines, int line_count, char *new_line);
void	*ft_free(char **arr, int count);
void 	free_split(char **arr);
int		ft_strcmp(const char *s1, const char *s2);

#endif