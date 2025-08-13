/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:27:02 by malaamir          #+#    #+#             */
/*   Updated: 2025/08/13 22:37:24 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* call once after load_textures(data) */
int load_reload_frames_simple(t_data *data)
{
    /* change these paths if your files are named differently */
	data->reload_frames[0]  = mlx_load_png("Bonus/textures/reload2/0.png");
    data->reload_frames[1]  = mlx_load_png("Bonus/textures/reload2/1.png");
    data->reload_frames[2]  = mlx_load_png("Bonus/textures/reload2/2.png");
    data->reload_frames[3]  = mlx_load_png("Bonus/textures/reload2/3.png");
    data->reload_frames[4]  = mlx_load_png("Bonus/textures/reload2/4.png");
    data->reload_frames[5]  = mlx_load_png("Bonus/textures/reload2/5.png");
    data->reload_frames[6]  = mlx_load_png("Bonus/textures/reload2/6.png");
    data->reload_frames[7]  = mlx_load_png("Bonus/textures/reload2/7.png");
    data->reload_frames[8]  = mlx_load_png("Bonus/textures/reload2/8.png");
    data->reload_frames[9]  = mlx_load_png("Bonus/textures/reload2/9.png");
    data->reload_frames[10]  = mlx_load_png("Bonus/textures/reload2/10.png");
    data->reload_frames[11] = mlx_load_png("Bonus/textures/reload2/11.png");
    data->reload_frames[12] = mlx_load_png("Bonus/textures/reload2/12.png");
    data->reload_frames[13] = mlx_load_png("Bonus/textures/reload2/13.png");
    data->reload_frames[14] = mlx_load_png("Bonus/textures/reload2/14.png");
    data->reload_frames[15] = mlx_load_png("Bonus/textures/reload2/15.png");
    data->reload_frames[16] = mlx_load_png("Bonus/textures/reload2/16.png");
    data->reload_frames[17] = mlx_load_png("Bonus/textures/reload2/17.png");
    data->reload_frames[18] = mlx_load_png("Bonus/textures/reload2/18.png");
    data->reload_frames[19] = mlx_load_png("Bonus/textures/reload2/19.png");
    data->reload_frames[20] = mlx_load_png("Bonus/textures/reload2/20.png");
    data->reload_frames[21] = mlx_load_png("Bonus/textures/reload2/21.png");
    data->reload_frames[22] = mlx_load_png("Bonus/textures/reload2/22.png");
    data->reload_frames[23] = mlx_load_png("Bonus/textures/reload2/23.png");
    data->reload_frames[24] = mlx_load_png("Bonus/textures/reload2/24.png");
    data->reload_frames[25] = mlx_load_png("Bonus/textures/reload2/25.png");


	data->reload_frame_count = 26;
	data->ticks_per_frame = 2; /* bigger = slower. default 6 (slower than your 2) */

    /* check simple failure (print and continue) */
    int i = 0;
    while (i < data->reload_frame_count)
    {
        if (data->reload_frames[i] == NULL)
        {
            printf("Failed to load reload frame %d\n", i);
        }
        i = i + 1;
    }

    return 0;
}
void start_reload_simple(t_data *data)
{
    if (data->reload_frame_count <= 0)
        return;
    data->reload_playing = 1;
    data->reload_current = 0;
    data->reload_tick = 0;
}

/* call every loop (in key_hook as shown below). Return 1 if a new frame is ready. */
int update_reload_simple(t_data *data)
{
    if (data->reload_playing == 0)
        return 0;
    data->reload_tick = data->reload_tick + 1;
    if (data->reload_tick >= data->ticks_per_frame)
    {
        data->reload_tick = 0;
        data->reload_current = data->reload_current + 1;
        if (data->reload_current >= data->reload_frame_count)
        {
            data->reload_playing = 0; /* stop at last frame */
            data->reload_current = data->reload_frame_count - 1;
        }
        return 1; /* tell caller to redraw */
    }
    return 0;
}

void free_reload_frames_simple(t_data *data)
{
    int i;
    i = 0;
    while (i < data->reload_frame_count)
    {
        if (data->reload_frames[i] != NULL)
            mlx_delete_texture(data->reload_frames[i]);
        i = i + 1;
    }
}

void draw_reload_overlay_simple(t_data *data)
{
    if (data->reload_frame_count <= 0)
        return;
    mlx_texture_t *t = data->reload_frames[data->reload_current];
    if (t == NULL)
        return;

    int fw = t->width;
    int fh = t->height;

    /* integer scale factor: set to 1 (original), 2 (double), 3 (triple), ... */
    int scale = 2; /* change this to make the image bigger */

    /* top-left position of the scaled image */
    int dest_fw = fw * scale;
    int dest_fh = fh * scale;
    int dest_x = MAP_WIDTH - dest_fw; /* keep it at right edge */
    int dest_y = MAP_HEIGHT - dest_fh; /* keep it at bottom edge */
    if (dest_x < 0)
        dest_x = 0;
    if (dest_y < 0)
        dest_y = 0;

    uint32_t *pixels = (uint32_t *)t->pixels;
    int sy = 0;
    while (sy < fh)
    {
        int sx = 0;
        while (sx < fw)
        {
            uint32_t col = pixels[sy * fw + sx];
            uint8_t a = (col >> 24) & 0xFF;
            if (a != 0) /* not fully transparent */
            {
                /* draw a scale x scale block for this source pixel */
                int by_off = 0;
                while (by_off < scale)
                {
                    int bx_off = 0;
                    while (bx_off < scale)
                    {
                        int bx = dest_x + sx * scale + bx_off;
                        int by = dest_y + sy * scale + by_off;
                        if (bx >= 0 && by >= 0 && bx < MAP_WIDTH && by < MAP_HEIGHT)
                            put_pixel(data, bx, by, col);
                        bx_off = bx_off + 1;
                    }
                    by_off = by_off + 1;
                }
            }
            sx = sx + 1;
        }
        sy = sy + 1;
    }
}

