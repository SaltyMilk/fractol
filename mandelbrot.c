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

int mandelbrot(t_fractol fract, t_mandelbrot *mb)
{
	int x;
	int y;
	unsigned int color = 0;
	int i;
	int tmp;

	mb->img_data = mlx_get_data_addr(fract.img_ptr, &tmp, &tmp, &tmp);
	y = 0;
	while (y < DWH)
	{
		x = 0;
		while (x < DWW)
		{
			mb->pr = 1.5 * (x - DWW  / 2) / (mb->zoom * DWW * 0.5) + mb->move_r;
			mb->pi = (y - DWH / 2) / (mb->zoom * DWH * 0.5) + mb->move_i;
			
			i = iterate_mandelbrot(mb);
			color = (i < MAX_ITERATION) ? ((16777216-MIN_COLOR) / MAX_ITERATION) * i + MIN_COLOR : 0;
			((unsigned int *)mb->img_data)[y * DWW + x] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fract.mlx_ptr, fract.win_ptr, fract.img_ptr, 0, 0);
	return (0);
}