/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:37:57 by eshana            #+#    #+#             */
/*   Updated: 2021/10/12 01:56:49 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cute_png.h"
#include "so_long_bonus.h"

double g_scale = 1;

static void	*mlx_png_file_to_image(void *mlx, char *file, int *width, int *height)
{
    cp_image_t	png_img;
    void		*mlx_img;
    cp_pixel_t 	*mlx_img_data;
    int			i;

    png_img = cp_load_png(file);
    if (png_img.pix == NULL)
    {
        printf("cp_load_png_fail: %s\n", file);
        return (NULL);
    }
    cp_premultiply(&png_img);
    if (g_scale < 1)
        mlx_img = mlx_new_image_alpha(mlx, png_img.w / g_scale, png_img.h / g_scale);
    else
        mlx_img = mlx_new_image_alpha(mlx, png_img.w, png_img.h);
    if (mlx_img == NULL)
    {
        free(png_img.pix);
        return (NULL);
    }
    mlx_img_data = (cp_pixel_t *)mlx_get_data_addr(mlx_img, &i, &i, &i);
    i = 0;
    int k = 1;
    int j = 0;
    while (k <= png_img.h)
    {
        while (i < png_img.w * k)
        {
            mlx_img_data[j].r = png_img.pix[i].b;
            mlx_img_data[j].g = png_img.pix[i].g;
            mlx_img_data[j].b = png_img.pix[i].r;
            mlx_img_data[j].a = png_img.pix[i].a;
            ++i;
            ++j;
        }
        k++;
        if (g_scale < 1)
            j += png_img.w / g_scale - png_img.h;
    }
//    while (i < png_img.w * png_img.h)
//    {
//        mlx_img_data[j].r = png_img.pix[i].b;
//        mlx_img_data[j].g = png_img.pix[i].g;
//        mlx_img_data[j].b = png_img.pix[i].r;
//        mlx_img_data[j].a = png_img.pix[i].a;
//        ++i;
//        ++j;
//    }
    if (g_scale < 1)
    {
        *width = png_img.w / g_scale;
        *height = png_img.h / g_scale;
    }
    else
    {
        *width = png_img.w;
        *height = png_img.h;
    }
    free(png_img.pix);
    return (mlx_img);
}

static int	ft_load_map_imgs(t_game *g, t_img img[8], const char *str)
{
	char	*s;
	int		i;

	s = ft_strdup(str);
	if (!s)
		return (-1);
	i = 0;
	while (i < 8)
	{
		s[ft_strlen(s) - 5] = '0' + i;
		img[i].ptr = mlx_png_file_to_image(g->mlx_ptr, s, &img[i].w, &img[i].h);
		if (!img[i].ptr)
		{
            printf("Fail to load: %s\n", str);
			free(s);
			return (-1);
		}
		i++;
	}
	free(s);
	return (0);
}

int	ft_png_to_arr(t_game *g, t_img img[4][10], char **s, int rot)
{
	int		i;

	if (!(*s))
		return (-1);
	i = 0;
	while (i < 10)
	{
		(*s)[ft_strlen(*s) - 5] = '0' + i;
		img[rot][i].ptr = mlx_png_file_to_image(g->mlx_ptr, *s,
				&img[rot][i].w, &img[rot][i].h);
		if (!img[rot][i].ptr)
		{
            printf("Fail to load: %s\n", *s);
			free(*s);
			return (-1);
		}
		i++;
	}
	free(*s);
	return (0);
}

static int	ft_load_rot_imgs(t_game *g, t_img img[6][9], char **s, int rot)
{
	int		i;

	if (!(*s))
		return (-1);
	i = 0;
	while (i < 9)
	{
		(*s)[ft_strlen(*s) - 5] = '0' + i;
		img[rot][i].ptr = mlx_png_file_to_image(g->mlx_ptr, *s,
				&img[rot][i].w, &img[rot][i].h);
		if (!img[rot][i].ptr)
		{
            printf("Fail to load: %s\n", *s);
			free(*s);
			return (-1);
		}
		i++;
	}
	free(*s);
	return (0);
}

static int	ft_load_character(t_game *g, t_character *ch, char *str)
{
	int		res;
	char	*path;

	res = 0;
	path = ft_strjoin(str, "/d/0.png");
	res += ft_png_to_arr(g, ch->img, &path, DWN);
	path = ft_strjoin(str, "/r/0.png");
	res += ft_png_to_arr(g, ch->img, &path, RGT);
	path = ft_strjoin(str, "/u/0.png");
	res += ft_png_to_arr(g, ch->img, &path, UP);
	path = ft_strjoin(str, "/l/0.png");
	res += ft_png_to_arr(g, ch->img, &path, LFT);
	path = ft_strjoin(str, "/dl/0.png");
	res += ft_load_rot_imgs(g, ch->ro, &path, DL);
	path = ft_strjoin(str, "/lu/0.png");
	res += ft_load_rot_imgs(g, ch->ro, &path, LU);
	path = ft_strjoin(str, "/ur/0.png");
	res += ft_load_rot_imgs(g, ch->ro, &path, UR);
	path = ft_strjoin(str, "/rd/0.png");
	res += ft_load_rot_imgs(g, ch->ro, &path, RD);
	path = ft_strjoin(str, "/du/0.png");
	res += ft_load_rot_imgs(g, ch->ro, &path, DU);
	path = ft_strjoin(str, "/lr/0.png");
	res += ft_load_rot_imgs(g, ch->ro, &path, LR);
	return (res);
}

int	ft_load_resources(t_game *g)
{
	static int	res;

    if (TILE * g->x_size == g->screen_x)
        g->scale = 1;
    else
        g->scale = (double)(TILE * g->x_size) / g->screen_x;
    printf("screen size: %dx%d, scale: %f\n", g->screen_x, g->screen_y, g->scale);
    g_scale = g->scale;
	res += ft_load_map_imgs(g, g->empty, "res/empty/0.png");
	res += ft_load_map_imgs(g, g->wall, "res/wall/0.png");
	res += ft_load_character(g, &g->player, "res/hero");
	res += ft_load_character(g, &g->enemy[0], "res/enemy/0");
	res += ft_load_character(g, &g->enemy[1], "res/enemy/1");
	res += ft_load_character(g, &g->enemy[2], "res/enemy/2");
	res += ft_load_eggs(g);
	g->exit_img.ptr = mlx_png_file_to_image(g->mlx_ptr,
			"res/exit.png", &(g->exit_img.w), &(g->exit_img.h));
	if (!g->exit_img.ptr)
		res--;
	if (res < 0)
		ft_putstr_fd("Error\nCan't load resources\n", 2);
	ft_initialize_game(g);
	return (res);
}
