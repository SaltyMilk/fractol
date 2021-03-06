/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:31:12 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/05 18:35:28 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <pthread.h>

# if __linux
#  define ESC 65307
#  define SCROLL_UP 5
#  define SCROLL_DOWN 4

#  define ARR_UP 65364
#  define ARR_DOWN 65362
#  define ARR_RIGHT 65363
#  define ARR_LEFT 65361
# else
#  define ESC 53
#  define SCROLL_UP 5
#  define SCROLL_DOWN 4

#  define ARR_UP 125
#  define ARR_DOWN 126
#  define ARR_RIGHT 124
#  define ARR_LEFT 123
# endif

# define DWW 1024
# define DWH 750
# define MOVE_VAL 0.1
# define M_C 65
# define TBM 16777216

/*
**VALUE SHOULDN'T BE ABOVE 16777216 && under or equal to 0 for MAX_ITERATION
*/

# ifndef MAX_ITER
#  define MAX_ITER 512
# endif

# define N_THREAD 4

struct s_fractol;

typedef struct		s_mandelbrot
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
}					t_mandelbrot;

typedef struct		s_fractol
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*juliamod_win;
	void			*img_ptr;
	int				(*func)(struct s_fractol *);
	t_mandelbrot	mb;
}					t_fractol;

typedef struct		s_thread_arg
{
	int				start;
	int				end;
	t_fractol		*f;
}					t_ta;

int					exit_hook(void);
int					key_hook(int keycode, t_fractol *param);
int					mouse_hook(int keycode, int x, int y, t_fractol *fract);
int					juliamod_hook(int x, int y, t_fractol *fract);
int					mandelbrot(t_fractol *fract);
int					juliaset(t_fractol *fract);
int					thirdfract(t_fractol *fract);
void				init_mandelbrot(t_mandelbrot *mb);

#endif
