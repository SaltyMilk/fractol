#ifndef FRACTOL_H
#define FRACTOL_H

#include "mlx/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <pthread.h>

#define DWW 1000
#define DWH 750
#define MOVE_VAL 0.1

#define ESC 53
#define SCROLL_UP 5
#define SCROLL_DOWN 3

#define N_THREAD 2

#define ARR_UP 125
#define ARR_DOWN 126
#define ARR_RIGHT 124
#define ARR_LEFT 123

#define MIN_COLOR 65
/*
**VALUE SHOULDN'T BE ABOVE 16777216 && under or equal to 0 for MAX_ITERATION
*/
#define MAX_ITERATION 256

typedef struct	s_mandelbrot
{
	double			pr;
	double			pi;
	double			old_r;
	double			old_i;
	double			f_r;
	double			f_i;
	double			zoom;
	double			move_r;
	double			move_i;
	char			*img_data;
	pthread_t		thread[N_THREAD];
	pthread_mutex_t mutex;
}				t_mandelbrot;

typedef struct	s_fractol
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_mandelbrot	mb;
}				t_fractol;


int		exit_hook(void);
int		key_hook(int keycode, t_fractol *param);
int		mouse_hook(int keycode, int x, int y, t_fractol *fract);
int		mandelbrot(t_fractol *fract);
void	init_mandelbrot(t_mandelbrot *mb);

#endif