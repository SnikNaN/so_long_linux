/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:17:12 by eshana            #+#    #+#             */
/*   Updated: 2021/10/12 08:18:17 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_free_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->y_size)
		{
			if (game->map[i])
				free((game->map)[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void    ft_free_character(t_character *ch, void *mlx_ptr)
{
    int i;
    int j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 10; j++)
        {
            mlx_destroy_image(mlx_ptr, ch->img[i][j].ptr);
        }
    for (i = 0; i < 6; i++)
        for (j = 0; j < 9; j++)
        {
            mlx_destroy_image(mlx_ptr, ch->ro[i][j].ptr);
        }
}

void    ft_free_sprites(t_game *g)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 10; j++)
            mlx_destroy_image(g->mlx_ptr, g->egg_img[i][j].ptr);
    for (int i = 0; i < 8; i++)
    {
        mlx_destroy_image(g->mlx_ptr, g->wall[i].ptr);
        mlx_destroy_image(g->mlx_ptr, g->empty[i].ptr);
    }
    mlx_destroy_image(g->mlx_ptr, g->exit_img.ptr);
}

int	ft_exit_success(t_game *game)
{
    mlx_loop_end(game->mlx_ptr);
	ft_free_map(game);
    //mlx_destroy_window(game->mlx_ptr, game->window);
    ft_free_sprites(game);
    ft_free_character(&game->player, game->mlx_ptr);
    for (int i = 0; i < 3; i++)
        ft_free_character(&game->enemy[i], game->mlx_ptr);
	ft_lstclear(&game->eggs, free);
    mlx_destroy_display(game->mlx_ptr);
    free(game->mlx_ptr);
	exit(EXIT_SUCCESS);
}
