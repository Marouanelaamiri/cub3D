/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/01 11:40:11 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
    int     map_rows;        /* number of rows in map       */
    int     map_cols;        /* number of cols (max width)  */

    double  player_x;        /* player start X (column +.5) */
    double  player_y;        /* player start Y (row +.5)    */
    char    player_dir;      /* 'N','S','E' or 'W'           */
}               t_parse;

int     parse_cubfile(const char *path, t_parse *p);
char    **read_lines(const char *path, int *line_count);
void    init_parse(t_parse *p);
void    parse_header(char *line, t_parse *p);
void    parse_resolution(char *line, t_parse *p);
void    parse_texture  (char *line, t_parse *p);
void    parse_color    (char *line, t_parse *p);
int     is_map_line(const char *line);
void    extract_map(char **lines, int start, t_parse *p);
void    pad_map    (t_parse *p);
void    validate_map    (t_parse *p);
void    free_parse(t_parse *p);
#endif