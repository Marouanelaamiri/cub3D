/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:26:32 by malaamir          #+#    #+#             */
/*   Updated: 2025/07/01 11:26:59 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int     parse_cubfile(const char *path, t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Top‑level: read, parse headers, build and validate map, set player.

char    **read_lines(const char *path, int *line_count);
// ────────────────────────────────────────────────────────────────────────────
// Read entire file into a NULL‑terminated array of strings.

void    init_parse(t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Zero‑out or set defaults for all fields in t_parse.

void    parse_header(char *line, t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Dispatch based on prefix (R, NO, SO, WE, EA, S, F, C).

void    parse_resolution(char *line, t_parse *p);
void    parse_texture  (char *line, t_parse *p);
void    parse_color    (char *line, t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Handle each header type; on error call exit_error().

int     is_map_line(const char *line);
// ────────────────────────────────────────────────────────────────────────────
// Return 1 if line contains only map chars (space,1,0,NSEW2).

void    extract_map(char **lines, int start, t_parse *p);
void    pad_map    (t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Copy from lines[start] to p->map, pad rows to p->map_cols.

void    validate_map    (t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Check enclosure, valid chars, single player; record player pos/dir.

void    free_parse(t_parse *p);
// ────────────────────────────────────────────────────────────────────────────
// Free p->map rows, texture strings, etc., on success or error.