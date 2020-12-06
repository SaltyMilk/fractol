#include <fractol.h>

int key_hook(int keycode, t_fractol *fract)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == ARR_UP)
	{
		fract->mb.move_i += MOVE_VAL / fract->mb.zoom;
		fract->func(fract);
	}
	else if (keycode == ARR_DOWN)
	{
		fract->mb.move_i -= MOVE_VAL / fract->mb.zoom;
		fract->func(fract);
	}
	else if (keycode == ARR_RIGHT)
	{
		fract->mb.move_r += MOVE_VAL / fract->mb.zoom;
		fract->func(fract);
	}
	else if (keycode == ARR_LEFT)
	{
		fract->mb.move_r -= MOVE_VAL / fract->mb.zoom;
		fract->func(fract);
	}
	return(19);
}

int juliamod_hook(int x, int y, t_fractol *fract)
{
	if (x >= 0 && x <= 250 && y >= 0 && y <= 250)
	{
	fract->mb.pr = 1.5 * (x) / (fract->mb.zoom * DWW * 0.5);
	fract->mb.pi = (y) / (fract->mb.zoom * DWH * 0.5);
//	printf("mouse moved\npr=%f|pi=%f\n", fract->mb.pr, fract->mb.pi);
	fract->func(fract);
	}
	return (42);
}

int mouse_hook(int keycode, int x, int y, t_fractol *fract)
{
	if (keycode == SCROLL_UP)
	{
		fract->mb.move_r += 1.5 * (x - DWW  / 2) / (fract->mb.zoom * DWW * 0.5);
		fract->mb.move_i += (y - DWH / 2) / (fract->mb.zoom * DWH * 0.5);
		fract->mb.zoom *= 1.1;
		fract->func(fract);
	}
	else if (keycode == SCROLL_DOWN)
	{
		fract->mb.zoom /= 1.1;
		fract->func(fract);
	}
	return(19);
}

int		exit_hook(void)
{
	exit(0);
	return (19);
}