#include "fractol.h"

void init_mandelbrot(t_mandelbrot *mb)
{
	ft_bzero(mb, sizeof(t_mandelbrot));
	mb->zoom = 1;
	mb->move_r = -0.5;
}

int iterate_mandelbrot(t_mandelbrot mb)
{
	int i;

	i = 0;
	mb.f_i = 0;
	mb.f_r = 0;
	while (i < MAX_ITERATION)
	{
		mb.old_i = mb.f_i;
		mb.old_r = mb.f_r;
		mb.f_i = 2 * mb.old_r * mb.old_i + mb.pi;
		mb.f_r =  mb.old_r * mb.old_r - mb.old_i * mb.old_i + mb.pr; 
		if ((mb.f_r * mb.f_r + mb.f_i * mb.f_i) > 4)
			return (i);
		i++;
	}
	return (i);
}

void mandeloop(t_fractol *f, t_mandelbrot mb, int start[2], int lim[2])
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
			i = iterate_mandelbrot(mb);
			color = (i < MAX_ITERATION) ? ((16777216-MIN_COLOR) / MAX_ITERATION) * i + MIN_COLOR : 0;
			pthread_mutex_lock(&f->mb.mutex);
			((unsigned int *)f->mb.img_data)[y * DWW + x] = color;
			pthread_mutex_unlock(&f->mb.mutex);
			x++;
		}
		y++;
	}

}


void *calc_pixels(void *fract)
{
	t_fractol *f = (t_fractol *)fract;
	static int n = -1;
	int id;
	int start[2];
	int lim[2];
	
	ft_bzero(start, sizeof(start));
	lim[0] = DWW;
	lim[1] = DWH;
	pthread_mutex_lock(&f->mb.mutex);
	id = ++n;
	if (id == 3)
		n = -1;
	pthread_mutex_unlock(&f->mb.mutex);
	if (id == 1 || id == 3)
		start[0] = DWW / 2;
/*	if (id == 2 || id == 3)
		start[1] = DWH / 2;*/
	if (id == 0 || id == 2)
		lim[0] /= 2;
/*	if (id == 0 || id == 1)
		lim[1] /= 2;*/
	mandeloop(f, f->mb, start, lim);
	return(NULL);
}

int mandelbrot(t_fractol *fract)
{
	int tmp;
	int i;

	i = 0;
	fract->mb.img_data = mlx_get_data_addr(fract->img_ptr, &tmp, &tmp, &tmp);
	pthread_mutex_init(&fract->mb.mutex, NULL);
	while (i < N_THREAD)
		if (pthread_create(&(fract->mb.thread[i++]), NULL, calc_pixels, (void *)fract))
			return (1);
	//calculate_each_pixel(fract);
	i = 0;
	while (i < N_THREAD)
		if (pthread_join(fract->mb.thread[i++], NULL))
			return (1);
	pthread_mutex_destroy(&fract->mb.mutex);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img_ptr, 0, 0);
	return (0);
}