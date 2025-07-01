/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/01 11:23:52 by malaamir         ###   ########.fr       */
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

#endif