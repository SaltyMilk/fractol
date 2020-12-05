/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:26:19 by sel-melc          #+#    #+#             */
/*   Updated: 2019/10/21 17:18:38 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rev_int_tab(int *tab, size_t size)
{
	int i;

	i = 0;
	if (tab)
		while ((size_t)i < size / 2)
		{
			ft_swap(&tab[i], &tab[size - i - 1]);
			i++;
		}
}