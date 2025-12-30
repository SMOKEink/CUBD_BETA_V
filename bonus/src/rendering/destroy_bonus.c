/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:00:24 by aachata           #+#    #+#             */
/*   Updated: 2025/12/30 19:19:36 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	clear_image(t_game *game)
{
	int	i;
	int	total;
	int	*img_data;

	img_data = (int *)game->frame.data_img;
	total = (game->frame.line_len / 4) * HEIGHT;
	i = -1;
	while (++i < total)
		img_data[i] = 0;
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_game(t_game *gm)
{
	if (gm->mlx && gm->win)
		mlx_mouse_show(gm->mlx, gm->win);
	free_textures(gm);
	if (gm->mlx && gm->frame.img)
		mlx_destroy_image(gm->mlx, gm->frame.img);
	if (gm->mlx && gm->win)
		mlx_destroy_window(gm->mlx, gm->win);
	if (gm->mlx)
	{
		mlx_destroy_display(gm->mlx);
		free(gm->mlx);
	}
	gc_free_all();
	exit(1);
}
