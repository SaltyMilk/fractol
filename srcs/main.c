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

void	handle_args(char **argv, t_fractol *f)
{
	int arg;

	if (ft_isdigit(argv[1][0]) && ((arg = atoi(argv[1])) || !arg))
	{
		if ((arg == 0 && (f->func = &mandelbrot)) 
		|| (arg == 1 && (f->func = &juliaset))
		|| (arg == 2 && (f->func = &thirdfract)))
			return ;
	}
	ft_putstr_fd("Arg err:\n0:mandelbrot\n1:juliaset\n2:thirdfract\n", 2);
	exit(2);
}
void hooks_f(t_fractol *f)
{
	mlx_key_hook(f->win_ptr, key_hook, f);
	mlx_hook(f->win_ptr, 4, 4, mouse_hook, f);
	mlx_hook(f->win_ptr, 17, 0, exit_hook, NULL);
	if (f->func == juliaset)
		mlx_hook(f->juliamod_win, 6, 64, juliamod_hook, f);
}

void start_fractol(t_fractol *f)
{
	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, DWW, DWH, "fractol");
	f->img_ptr = mlx_new_image(f->mlx_ptr, DWW, DWH);
	init_mandelbrot(&f->mb);
	if (f->func == juliaset)
		f->juliamod_win = mlx_new_window(f->mlx_ptr, 250, 250, "Julia modifier");
	f->func(f);
	hooks_f(f);
	mlx_loop(f->mlx_ptr);
}

pid_t multiple_args(char **argv, t_fractol *f)
{
	pid_t	pid;
	int		arg;
	
	if ((pid = fork()) == -1)
		return (-1);
	if (!pid)
		handle_args(argv, f);
	else
	{
		if (ft_isdigit(argv[2][0]) && ((arg = atoi(argv[2])) || !arg))
		{
			if ((arg == 0 && (f->func = &mandelbrot)) 
			|| (arg == 1 && (f->func = &juliaset))
			|| (arg == 2 && (f->func = &thirdfract)))
				return (pid);
		}
		ft_putstr_fd("Arg err:\n0:mandelbrot\n1:juliaset\n2:thirdfract\n", 2);
		exit(2);	
	}
	return (pid);
}

int		main(int argc, char **argv)
{
	t_fractol	f;
	pid_t		pid;

	if (argc == 2)
		handle_args(argv, &f);
	else if (argc == 3)
	{
		if ((pid = multiple_args(argv, &f)) == -1)
			return (1);
		start_fractol(&f);
		waitpid(pid, NULL, 0);
		exit(0);
	}
	else
	{
		ft_putstr_fd("Arg err:\n0:mandelbrot\n1:juliaset\n2:thirdfract\n", 2);
		exit(2);	
	}
	start_fractol(&f);
}
