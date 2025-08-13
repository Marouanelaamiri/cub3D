/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/14 00:15:04 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# define TILE_SIZE 64
# define COLLIDE_PAD 0.3f
# define RENDER_PAD  0.3f
# define SPEED 0.15f
# define FOV 1
# define BUFFER_SIZE 42
# define MAP_WIDTH 1920
# define MAP_HEIGHT 1080
# define DOOR_CLOSED 'D'
# define DOOR_OPEN   'd'

typedef struct s_algo
{
	float	px;
	float	py;
	float	dir_x;
	float	dir_y;
	int		map_x;
	int		map_y;
	float	delta_x;
	float	delta_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		side;
}	t_algo;

typedef struct s_data
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			hit_side;
	float			hit_wall_x;
	mlx_texture_t *reload_frames[30];
	int            reload_frame_count;   /* will be 29 */
	int            reload_current;       /* current frame index 0..28 */
	int            reload_playing;       /* 0 = stopped, 1 = playing */
	int            reload_tick;          /* increment each loop */
	int            ticks_per_frame;   
	int            reload_margin_right;   /* smaller => more to the right */
	int            reload_margin_bottom;  /* smaller => more down */
	int door_open;       /* 0 = no open door being tracked, 1 = a door is open */
	int door_x;          /* tile x of currently-open door */
	int door_y;          /* tile y of currently-open door */
	int door_nx;         /* normal x component when opened: -1, 0 or 1 */
	int door_ny;         /* normal y component when opened: -1, 0 or 1 */
	mlx_texture_t	*tex;
	float			tex_x;
	float			tex_y;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*door;
	int				hit_is_door;
	mlx_image_t		*img;
	uint32_t		f_color;
	uint32_t		c_color;
	void			*mlx;
	void			*win;
	float			fov;
	float			ray_angle;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	char			**map;
	char			player_char;
	float			player_angle;
	int				map_width;
	int				recmap_with;
	int				map_height;
	int				recmap_height;
	int				player_count;
	int				config_count;
	int				map_parsed;
	float			player_x;
	float			player_y;
	char			player_direction;
	int				has_error;
	char			*error_message;
	t_algo			*algo;
}	t_data;

void	assign_floor_color(t_data *info, int r, int g, int b);
void	assign_ceiling_color(t_data *info, int r, int g, int b);
void	validate_floor_rgb(int r, int g, int b, t_data *info);
void	validate_ceiling_rgb(int r, int g, int b, t_data *info);
void	clean_map(t_data *info);
t_data	*parser_map(int ac, char **av);
void	free_malloc(t_data *info, char *line, char **valid_map, int height);
size_t	get_max_line_length(t_data *info);
void	clean_map_arr(t_data *info);
void	clean_map(t_data *info);
char	*trimming_line(char *line, t_data *info);
void	init_data(t_data *info);
void	update_map(t_data *info, char **valid_map, char *checked);
void	copy_existing_map(t_data *info, char **valid_map);
int		check_texture_path(char *path);
int		check_id(char *line, t_data *info);
void	print_error(char *msg, t_data *info);
void	check_surround(t_data *info, int i, int j, int len);
int		check_comma(char *line);
int		check_c_format(char *color);
int		check_c_range(char **colors);
int		check_color(char *color);
void	check_config(t_data *info);
int		check_empty_line(char *line, t_data *info, int *start);
int		check_line(char *line, t_data *info, int *started);
int		final_check(t_data *info);
void	check_arguments(int ac, char **av);
t_data	*malloc_map(void);
t_data	*parser_map(int ac, char **av);
int		parse_color(char *str, t_data *info, int is_floor);
void	check_map_char(t_data *info, int i, int len);
void	check_line_for_player(t_data *info, int i, int len);
void	map_parsing(t_data *info, int *started, char *line);
int		handle_fc(char *trim, t_data *info);
void	check_map_line(t_data *info, char *line);
int		validate_map_file(char *path, t_data *info);
void	check_borders(t_data *info);
void	ft_free_array(char **arr);
int		load_textures(t_data *data);
void	replace_spaces_with_zero(t_data *data);
void	pad_map_edges_with_walls(t_data *info);
void	debug_print_map(t_data *info); // need to be removed
int		ft_getmax(int a, int b);
int		ft_whitespaces(int c);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
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
void	free_split(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_retate(t_data *data, int flag);
int		key_w(t_data *data, int flag, float new_x, float new_y);
int		key_s(t_data *data, int flag, float new_x, float new_y);
int		key_a(t_data *data, int flag, float new_x, float new_y);
int		key_d(t_data *data, int flag, float new_x, float new_y);
int		is_colliding(t_data *data, float new_px, float new_py);
float	cast_ray(t_data *data, float angle);
int		main_raycasting(t_data *data);
void	put_pixel(t_data *d, int x, int y, uint32_t color);
void	set_wh_map(t_data *data);
void	set_fov(t_data *data, float fov);
void	set_char(t_data *data, char c);
float	get_angle_from_dir(char dir);
void	redraw(t_data *data);
void	init_struct(t_data *data);
void	init_player(t_data *data);
int		validate_token(const char *s);
void	color_error_or_exit(char *value, t_data *info, int is_floor);

int load_reload_frames_simple(t_data *data);
void start_reload_simple(t_data *data);
int update_reload_simple(t_data *data);
void free_reload_frames_simple(t_data *data);
void draw_reload_overlay_simple(t_data *data);
void toggle_door(t_data *data);
int update_auto_close_door(t_data *data);

#endif