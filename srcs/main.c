#include <fractol.h>

void handle_args(int argc, char **argv, t_fractol *f)
{
	int arg;

	if (argc == 2)
		if (ft_isdigit(argv[1][0]))
		{
			arg = atoi(argv[1]);
			if (arg == 0 && (f->func = &mandelbrot))
				return;
			else if (arg == 1 && (f->func = &juliaset))
				return ;
			else if (arg == 2 && (f->func = &thirdfract))
				return;
		}
	ft_putstr_fd("Arg err, list of args:\n0:mandelbrot\n1:juliaset\n2:thirdfract", 2);
	exit(2);
}

int main(int argc, char **argv)
{
	t_fractol f;

	handle_args(argc, argv, &f);
	f.mlx_ptr = mlx_init();
	f.win_ptr = mlx_new_window(f.mlx_ptr, DWW, DWH, "fractol");
	f.img_ptr = mlx_new_image(f.mlx_ptr, DWW, DWH);
	init_mandelbrot(&f.mb);
	if (f.func == juliaset)
		f.juliamod_win = mlx_new_window(f.mlx_ptr, 250, 250, "Julia modifier");
	f.func(&f);
	mlx_key_hook(f.win_ptr, key_hook, &f);
	mlx_hook(f.win_ptr, 4, 4, mouse_hook, &f);
	mlx_hook(f.win_ptr, 17, 0, exit_hook, NULL);
	if (f.func == juliaset)
		mlx_hook(f.juliamod_win, 6, 64, juliamod_hook, &f);
	mlx_loop(f.mlx_ptr);
}