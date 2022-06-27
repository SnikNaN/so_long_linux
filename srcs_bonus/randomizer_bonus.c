/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by eshana            #+#    #+#             */
/*   Updated: 2021/10/09 00:07:30 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_rnd(int *seed, int lim)
{
	int	i;

	if (*seed < 0)
		*seed = -*seed;
	*seed = (*seed * 32719 + 3) % 32749;
	i = (*seed % lim);
	return (i);
}
