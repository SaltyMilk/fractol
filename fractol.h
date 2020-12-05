#ifndef FRACTOL_H
#define FRACTOL_H

#include "mlx/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdio.h>

#define ESC 53
#define DWW 1000 //DEFAULT WINDOW WIDTH
#define DWH 750//DEFAULT WINDOW HEIGHT

//VALUE SHOULDN'T BE ABOVE 16777216 && under or equal to 0
#define MAX_ITERATION 256

typedef struct	s_mandelbrot //
{
	double	pr;//Real position 
	double	pi;//Imaginary position
	double	old_r;
	double	old_i;
	double	f_r;
	double	f_i;
	double	zoom;
	double	move_r;
	double	move_i;
}				t_mandelbrot;

typedef struct	s_fractol
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mandelbrot mb;
}				t_fractol;


int		exit_hook(void);
int		key_hook(int keycode, t_fractol *param);
int		mandelbrot(t_fractol fract, t_mandelbrot *mb);
void	init_mandelbrot(t_mandelbrot *mb);

#endif