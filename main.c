#include "fractol.h"
void handle_args(int argc, char **argv, t_fractol *f)
{
	int arg;

	if (argc == 2)
	{
		if (ft_isdigit(argv[1][0]))
		{
			arg = atoi(argv[1]);
			if (arg == 0)
			{
				f->func = &mandelbrot;
				return;
			}
			else if (arg == 1)
			{
				f->func = &juliaset;
				return ;
			}
		}
	}
	ft_putstr_fd("Arg err, list of args:\n0:mandelbrot\n1:juliaset\n", 2);
	exit(2);
}

int main(int argc, char **argv)
{
	t_fractol fract;

	handle_args(argc, argv, &fract);
	fract.mlx_ptr = mlx_init();
	fract.win_ptr = mlx_new_window(fract.mlx_ptr, DWW, DWH, "fractol");
	fract.img_ptr = mlx_new_image(fract.mlx_ptr, DWW, DWH);
	init_mandelbrot(&fract.mb);
	fract.func(&fract);
	mlx_key_hook(fract.win_ptr, key_hook, &fract);
	mlx_hook(fract.win_ptr, 4, 4, mouse_hook, &fract);
	mlx_hook(fract.win_ptr, 17, 0, exit_hook, NULL);
	mlx_loop(fract.mlx_ptr);
}