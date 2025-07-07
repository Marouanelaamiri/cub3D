/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/08 00:27:12 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define BUFFER_SIZE	1024
# define TILE_SIZE		60
# define RED 0xFF0000
# define BLACK 0x000000
# define GREEN 0x00FF00

typedef struct s_data
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	char *f_color;
	char *c_color;
	void *mlx;
	void *win;
	void    *img;
	char    *addr; 
	int     bpp;
    int     line_len;
    int     endian;
	char **map;
	int map_width;
	int recmap_with;
	int map_height;
	int recmap_height;
	int player_count;
	int config_count;
	int map_parsed;
	float player_x;
	float player_y;
	char	player_direction;
	int has_error;
	char *error_message;
}	t_data;

int put_map_2dv(t_data *data);
void	clean_map(t_data *info);
t_data	*parser_map(int ac, char **av);
void free_malloc(t_data *info, char *line, char **valid_map , int height);
size_t get_max_line_length(t_data *info);
void clean_map_arr(t_data *info);
void clean_map(t_data *info);
char *trimming_line(char *line, t_data *info);
void init_data(t_data *info);
void update_map(t_data *info, char **valid_map, char *checked);
void copy_existing_map(t_data *info, char **valid_map);
int check_texture_path(char *path);
// int check_so_no(char *trimmed, t_data *info);
// int check_we_ea(char *trimmed, t_data *info);
// int check_floor_ceiling(char *trimmed, t_data *info);
int check_id(char *line, t_data *info);
void print_error(char *msg, t_data *info);
void check_surround(t_data *info, int i, int j, int len);
int check_comma(char *line);
int check_c_format(char *color);
int check_c_range(char **colors);
int check_color(char *color);
void check_config(t_data *info);
int check_empty_line(char *line, t_data *info, int *start);
void map_parsing(t_data *info, int *started, char *line);
int check_line(char *line, t_data *info, int *started);
int final_check(t_data *info);
void check_arguments(int ac, char **av);
t_data	*malloc_map(void);
t_data *parser_map(int ac, char **av);
void check_map_char(t_data *info, int i, int len);
void	check_line_for_player(t_data *info, int i, int len);
// void check_player_pos(char c, int x, t_data *info, int height);
// void check_lines_char(char *checked, t_data *info, int height);
void check_map_line(t_data *info, char *line);
int check_file_lines(int fd, t_data *info, int *start);
int check_if_file_open(char *file, t_data *info, int *fd);
int is_valid_map_line(char *line, t_data *info);
void	horizontal_check(t_data*info, int len_max);
void vertical_check(t_data *info, int i, int len);
void check_borders(t_data *info);
void	ft_free_array(char **arr);
//============================================================//
int	ft_getmax(int a, int b);
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
char	*get_next_line(int fd);
char	*ft_joinfree(char *buffer, char *new_buffer);
char	*get_remaning(char *buffer);
char	*ft_getline(char *buffer);
char	*read_from_file(int fd, char *buffer);
char	**ft_realloc(char **lines, int line_count, char *new_line);
void	*ft_free(char **arr, int count);
void 	free_split(char **arr);
int		ft_strcmp(const char *s1, const char *s2);

#endif