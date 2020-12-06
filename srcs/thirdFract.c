#include <fractol.h>

int iterate_third(t_mandelbrot mb)
{
	int i;

	i = 0;
	mb.f_i = 0;
	mb.f_r = 0;
	while (i < MAX_ITERATION)
	{
		mb.old_i = mb.f_i;
		mb.old_r = mb.f_r;
		mb.f_i = 2 * mb.old_r * mb.old_i + mb.pi - mb.old_i;
		mb.f_r =  mb.old_r * mb.old_r - mb.old_i * mb.old_i + mb.pr - mb.old_r; 
		if ((mb.f_r * mb.f_r + mb.f_i * mb.f_i) > 4)
			return (i);
		i++;
	}
	return (i);
}

void thirdloop(t_fractol *f, t_mandelbrot mb, int start[2], int lim[2])
{
	int x;
	int y;
	int i;
	unsigned color;
	y = start[1];
	while (y < lim[1])
	{
		x = start[0];
		while (x < lim[0])
		{
			mb.pr = 1.5 * (x - DWW  / 2) / (mb.zoom * DWW * 0.5) + mb.move_r;
			mb.pi = (y - DWH / 2) / (mb.zoom * DWH * 0.5) + mb.move_i;		
			i = iterate_third(mb);
			color = (i < MAX_ITERATION) ? ((16777216-MIN_COLOR) / MAX_ITERATION) * i + MIN_COLOR : 0;
			((unsigned int *)f->mb.img_data)[y * DWW + x] = color;
			x++;
		}
		y++;
	}
}


void *tcalc_pixels(void *ta)
{
	t_fractol *f = ((t_ta*)ta)->f;
	int start[2];
	int lim[2];
	
	ft_bzero(start, sizeof(start));
	lim[0] = DWW;
	lim[1] = DWH;
	start[0] = ((t_ta *)ta)->start;
	lim[0] = ((t_ta *)ta)->end;
	thirdloop(f, f->mb, start, lim);
	return(NULL);
}

int thirdfract(t_fractol *fract)
{
	int tmp;
	int i;
	t_ta ta[N_THREAD];

	i = 0;
	fract->mb.img_data = mlx_get_data_addr(fract->img_ptr, &tmp, &tmp, &tmp);
	while (i < N_THREAD)
	{
		ta[i].f = fract;
		ta[i].start = (DWW / N_THREAD) * i;
		ta[i].end = (DWW / N_THREAD )* (i + 1);
		if (pthread_create(&(fract->mb.thread[i]), NULL, tcalc_pixels, (void *)&(ta[i])))
			return (1);
		i++;
	}
	i = 0;
	while (i < N_THREAD)
		if (pthread_join(fract->mb.thread[i++], NULL))
			return (1);
	pthread_mutex_destroy(&fract->mb.mutex);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img_ptr, 0, 0);
	return (0);
}