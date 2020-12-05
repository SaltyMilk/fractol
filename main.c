#include "fractol.h"
int main()
{
	t_fractol fract;

	fract.mlx_ptr = mlx_init();
	fract.win_ptr = mlx_new_window(fract.mlx_ptr, DWW, DWH, "fractol");
	fract.img_ptr = mlx_new_image(fract.mlx_ptr, DWW, DWH);
	init_mandelbrot(&fract.mb);
	mandelbrot(fract, &fract.mb);
	puts("Done mandelbrotting");
	mlx_key_hook(fract.win_ptr, key_hook, &fract);
	mlx_hook(fract.win_ptr, 4, 4, mouse_hook, &fract);
	mlx_hook(fract.win_ptr, 17, 0, exit_hook, NULL);
	mlx_loop(fract.mlx_ptr);
}