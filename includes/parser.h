/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/04 14:02:25 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

typedef struct s_parse
{
    int     screen_w;        /* screen width   */
    int     screen_h;        /* screen height  */

    char    *tex_no;         /* path to North wall texture */
    char    *tex_so;         /* path to South wall texture */
    char    *tex_we;         /* path to West  wall texture */
    char    *tex_ea;         /* path to East  wall texture */
    char    *tex_s;          /* path to sprite texture      */

    int     floor_col;       /* packed RGB floor color      */
    int     ceil_col;        /* packed RGB ceiling color    */

    char    **map;           /* padded, NULL‑terminated map  */
	char	*line;        /* current line being parsed    */
	char   *map_line;     /* lines read from file         */
    int     map_rows;        /* number of rows in map       */
    int     map_cols;        /* number of cols (max width)  */

    double  player_x;        /* player start X (column +.5) */
    double  player_y;        /* player start Y (row +.5)    */
    char    player_dir;      /* 'N','S','E' or 'W'           */
}               t_parse;




int map_err(t_parse *p);
void error_parsing(t_parse *p , char *error_msg);
void set_player_pos(t_parse *p, char dir, int i, int j);
void set_size(t_parse *p, char **arr, int i, int j);
void check_stats(t_parse *p);
int get_stats(t_parse *p, char *line);
void fix_map(t_parse *p);
void read_map(int fd, t_parse *p);
int pars_map(t_parse *p, int fd);
void check_texture_path(t_parse *p, char **path, char **split);
int pars_colors(char *line);
int check_colors(int *rgb, char *line);

void get_color(t_parse *p, int *rgb, char **split);
//============================================================//
int	ft_whitespaces(int c);
int	ft_atoi(const char *str);
void ft_bzero(void *s, size_t n);
void *ft_calloc(size_t count, size_t size);
int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_getline(char *buffer);
char	*get_remaning(char *buffer);
char	*ft_joinfree(char *buffer, char *new_buffer);
char	*get_next_line(int fd);
char	*read_from_file(int fd, char *buffer);
// char	**ft_realloc(char **lines, int line_count, char *new_line);
//============================================================//
void print_error_exit(const char *msg);
int ft_check_extension(char *av);
int ft_check_file(char *av);
void init_parse(t_parse *p);
int checking_char(char c, char *valid);
int ft_strlen_nonl(char *s);
char *ft_resize(char *str, size_t new_size);
char *strjoin_cub3d(char *s1, char *s2);
void free_2d_array(char **arr);
//============================================================//
int col_check(char **col, int y, int x, int size_y);
int check_vertical_walls(t_parse *p, int rows, int cols);
int check_horizontal_walls(t_parse *p, int rows, int cols);
int line_check(t_parse *p, char *line, int x);
int wall_check(t_parse *p);

#endif