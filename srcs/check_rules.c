/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 23:28:56 by eshana            #+#    #+#             */
/*   Updated: 2021/10/12 10:26:20 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_valid_sym(char *c, t_game *game)
{
	if (*c == '0' || *c == '1' || *c == 'E' || *c == 'C' || *c == 'P')
	{
		if (*c == '0')
			*c = (char)ft_rnd(&game->seed, 8);
		return (1);
	}
	else
		return (0);
}

static int	ft_check_walls(t_game *game)
{
	static int	x;
	static int	y;

	x = (int)ft_strlen((game->map)[y]);
	while (y < game->y)
	{
		if ((int)ft_strlen((game->map)[y]) != x)
			return (-2);
		y++;
	}
	x = 0;
	while (x < game->x)
	{
		if ((game->map)[0][x] != '1' || (game->map)[game->y - 1][x] != '1')
			return (-1);
		x++;
	}
	y = 0;
	while (y < game->y)
	{
		if ((game->map)[y][0] != '1' || (game->map)[y][game->x - 1] != '1')
			return (-1);
		y++;
	}
	return (0);
}

static void	ft_set_start(t_game *game, int x, int y, int *cnt)
{
	game->player.x = x;
	game->player.y = y;
    game->shield = 0;
    game->secret = '1';//(char)(ft_rnd(&game->seed, 8) + '1');
	(game->map)[y][x] = (char)ft_rnd(&game->seed, 8);
	(*cnt)++;
}

static int	ft_check_minimal(t_game *game)
{
	static int	x;
	static int	y;
	static int	exits;
	static int	start_p;

	while (y < game->y)
	{
		x = 0;
		while (x < game->x)
		{
			if (!ft_valid_sym(&(game->map)[y][x], game))
				return (-2);
			if ((game->map)[y][x] == 'C')
				game->collect.cnt++;
			if ((game->map)[y][x] == 'E')
				exits++;
			if ((game->map)[y][x] == 'P')
				ft_set_start(game, x, y, &start_p);
			x++;
		}
		y++;
	}
	if (!(game->collect.cnt) || !exits || start_p != 1)
		return (-1);
	return (0);
}

int	ft_check_rules(t_game *game)
{
	int	check;

	game->seed = (int)&game->mlx_ptr >> 16;
	game->x = (int)ft_strlen((game->map)[0]);
	game->collect.cnt = 0;
	check = ft_check_walls(game);
	if (check < 0)
	{
		ft_putstr_fd("Error\n", 2);
		if (check == -2)
			ft_putstr_fd("The map must be rectangular\n", 2);
		if (check == -1)
			ft_putstr_fd("The map must be surrounded by walls\n", 2);
		return (-1);
	}
	check = ft_check_minimal(game);
	if (check < 0)
	{
		ft_putstr_fd("Error\n", 2);
		if (check == -1)
			ft_putstr_fd("Map minimal requirements check failed\n", 2);
		if (check == -2)
			ft_putstr_fd("There are invalid symbols in the map file\n", 2);
	}
	return (check);
}
