#include "fractol.h"

int key_hook(int keycode, t_fractol *fract)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == 4)
	{
		fract->mb.zoom *= 1.001;
		mandelbrot(*fract, &fract->mb);
	}
	else if (keycode == 5)
	{
		fract->mb.zoom /= 1.001;
		mandelbrot(*fract, &fract->mb);
	}
	return(19);
}

int		exit_hook(void)
{
	exit(0);
	return (19);
}