/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:01:42 by aachata           #+#    #+#             */
/*   Updated: 2025/12/30 19:20:12 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_tex(t_game *gm, int idx, const char *path)
{
	t_tex	*t;

	t = &gm->wall[idx];
	t->img = mlx_xpm_file_to_image(gm->mlx, (char *)path, &t->w, &t->h);
	if (!t->img)
	{
		printf("Error\nTexture load failed: %s\n", path);
		destroy_game(gm);
		return (1);
	}
	t->data = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	if (!t->data)
	{
		printf("Error\nData addr failed: %s\n", path);
		destroy_game(gm);
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
		if (load_tex(gm, i, gm->tex_path[i]))
			return (1);
		i++;
	}
	return (0);
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
}
