/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:00:08 by aachata           #+#    #+#             */
/*   Updated: 2025/12/24 21:00:09 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	load_tex_any(t_game *gm, t_tex *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(gm->mlx, (char *)path, &tex->w, &tex->h);
	if (!tex->img)
	{
		fprintf(stderr, "Texture load failed: %s\n", path);
		destroy_game(gm, "Quitting...");
		return (1);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->data)
	{
		fprintf(stderr, "Data addr failed: %s\n", path);
		destroy_game(gm, "Quitting...");
		return (1);
	}
	return (0);
}

int	load_tex_wall(t_game *gm, int idx, const char *path)
{
	t_tex	*t;

	t = &gm->wall[idx];
	t->img = mlx_xpm_file_to_image(gm->mlx, (char *)path, &t->w, &t->h);
	if (!t->img)
	{
		fprintf(stderr, "Texture load failed: %s\n", path);
		destroy_game(gm, "Quitting...");
		return (1);
	}
	t->data = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	if (!t->data)
	{
		fprintf(stderr, "Data addr failed: %s\n", path);
		destroy_game(gm, "Quitting...");
		return (1);
	}
	return (0);
}

int	load_textures(t_game *gm)
{
	int	i;

	i = 0;
	while (i < TEX_WALL_COUNT)
	{
		if (load_tex_wall(gm, i, gm->tex_path[i]))
			return (1);
		i++;
	}
	if (gm->door_path && load_tex_any(gm, &gm->door, gm->door_path))
		return (1);
	if (gm->hand_path && load_tex_any(gm, &gm->hand, gm->hand_path))
		return (1);
	return (0);
}

void	free_door_hands(t_game *gm)
{
	if (gm->door_path)
	{
		if (gm->door.img && gm->mlx)
			mlx_destroy_image(gm->mlx, gm->door.img);
		gm->door.img = NULL;
		gm->door.data = NULL;
		gm->door_path = NULL;
	}
	if (gm->hand_path)
	{
		if (gm->hand.img && gm->mlx)
			mlx_destroy_image(gm->mlx, gm->hand.img);
		gm->hand.img = NULL;
		gm->hand.data = NULL;
		gm->hand_path = NULL;
	}
}

void	free_textures(t_game *gm)
{
	int	i;

	i = 0;
	while (i < TEX_WALL_COUNT)
	{
		if (gm->wall[i].img && gm->mlx)
			mlx_destroy_image(gm->mlx, gm->wall[i].img);
		gm->wall[i].img = NULL;
		gm->wall[i].data = NULL;
		i++;
	}
	free_door_hands(gm);
}
