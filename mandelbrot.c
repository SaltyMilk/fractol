#include "fractol.h"

void init_mandelbrot(t_mandelbrot *mb)
{
	ft_bzero(mb, sizeof(t_mandelbrot));
	mb->zoom = 1;
	mb->move_r = -0.5;
}

int iterate_mandelbrot(t_mandelbrot *mb)
{
	int i;

	i = 0;
	mb->f_i = 0;
	mb->f_r = 0;
	while (i < MAX_ITERATION)
	{
		mb->old_i = mb->f_i;
		mb->old_r = mb->f_r;
		mb->f_i = 2 * mb->old_r * mb->old_i + mb->pi;
		mb->f_r =  mb->old_r * mb->old_r - mb->old_i * mb->old_i + mb->pr; 
		if ((mb->f_r * mb->f_r + mb->f_i * mb->f_i) > 4)
			return (i);
		i++;
	}
	return (i);
}

void calculate_each_pixel(t_fractol *f)
{
	int x;
	int y;
	int i;
	unsigned int color;

	y = 0;
	while (y < DWH)
	{
		x = 0;
		while (x < DWW)
		{
			f->mb.pr = 1.5 * (x - DWW  / 2) / (f->mb.zoom * DWW * 0.5) + f->mb.move_r;
			f->mb.pi = (y - DWH / 2) / (f->mb.zoom * DWH * 0.5) + f->mb.move_i;
			
			i = iterate_mandelbrot(&f->mb);
			color = (i < MAX_ITERATION) ? ((16777216-MIN_COLOR) / MAX_ITERATION) * i + MIN_COLOR : 0;
			((unsigned int *)f->mb.img_data)[y * DWW + x] = color;
			x++;
		}
		y++;
	}
}

int mandelbrot(t_fractol *fract, t_mandelbrot *mb)
{
	int tmp;
	(void)mb;
	mb->img_data = mlx_get_data_addr(fract->img_ptr, &tmp, &tmp, &tmp);
	calculate_each_pixel(fract);

	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img_ptr, 0, 0);
	return (0);
}