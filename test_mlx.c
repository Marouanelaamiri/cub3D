#include "NEWMLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH  400
#define HEIGHT 300

int main(void)
{
    // 1. Initialize MLX42
    if (mlx_init(WIDTH, HEIGHT, "MLX42 Pixel Test", false) == NULL)
    {
        puts("mlx_init failed");
        return EXIT_FAILURE;
    }

    mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Pixel Test", false);

    // 2. Create a blank image
    mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        puts("mlx_new_image failed");
        return EXIT_FAILURE;
    }

    // 3. Set every pixel in the image (e.g. horizontal gradient)
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            // Create gradient color (red to green)
            uint8_t r = (uint8_t)(255 * x / WIDTH);
            uint8_t g = (uint8_t)(255 * y / HEIGHT);
            uint8_t b = 0;
            uint32_t color = (0xFF << 24) | (r << 16) | (g << 8) | b;

            mlx_put_pixel(img, x, y, color);
        }
    }

    // 4. Show the image in the window at (0,0)
    mlx_image_to_window(mlx, img, 0, 0);

    // 5. Enter main loop
    mlx_loop(mlx);

    // 6. Cleanup happens automatically
    return EXIT_SUCCESS;
}
