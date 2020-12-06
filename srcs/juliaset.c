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

#include <fractol.h>

int		iterate_juliaset(t_mandelbrot mb)
{
	int i;

	i = 0;
	while (i < MAX_ITER)
	{
		mb.old_i = mb.f_i;
		mb.old_r = mb.f_r;
		mb.f_i = 2 * mb.old_r * mb.old_i + mb.pi;
		mb.f_r = mb.old_r * mb.old_r - mb.old_i * mb.old_i + mb.pr;
		if ((mb.f_r * mb.f_r + mb.f_i * mb.f_i) > 4)
			return (i);
		i++;
	}
	return (i);
}

void	juloop(t_fractol *f, t_mandelbrot mb, int start[2], int lim[2])
{
	int			x;
	int			y;
	int			i;
	unsigned	c;

	y = start[1];
	while (y < lim[1])
	{
		x = start[0];
		while (x < lim[0])
		{
			mb.f_r = 1.5 * (x - DWW / 2) / (mb.zoom * DWW * 0.5) + mb.move_r;
			mb.f_i = (y - DWH / 2) / (mb.zoom * DWH * 0.5) + mb.move_i;
			i = iterate_juliaset(mb);
			c = (i < MAX_ITER) ? ((TBM - M_C) / MAX_ITER) * i + M_C : 0;
			((unsigned int *)f->mb.img_data)[y * DWW + x] = c;
			x++;
		}
		y++;
	}
}

void	*jcalc_pixels(void *ta)
{
	t_fractol	*f;
	int			start[2];
	int			lim[2];

	f = ((t_ta *)ta)->f;
	ft_bzero(start, sizeof(start));
	lim[0] = DWW;
	lim[1] = DWH;
	start[0] = ((t_ta *)ta)->start;
	lim[0] = ((t_ta *)ta)->end;
	juloop(f, f->mb, start, lim);
	return (NULL);
}

int		juliaset(t_fractol *f)
{
	int		tmp;
	int		i;
	t_ta	ta[N_THREAD];

	i = 0;
	f->mb.img_data = mlx_get_data_addr(f->img_ptr, &tmp, &tmp, &tmp);
	while (i < N_THREAD)
	{
		ta[i].f = f;
		ta[i].start = (DWW / N_THREAD) * (i);
		ta[i].end = (DWW / N_THREAD) * (i + 1);
		pthread_create(&(f->mb.thread[i]), 0, jcalc_pixels, (void *)&(ta[i]));
		i++;
	}
	i = 0;
	while (i < N_THREAD)
		pthread_join(f->mb.thread[i++], 0);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img_ptr, 0, 0);
	return (0);
}
