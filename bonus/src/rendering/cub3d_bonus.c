/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makevali <makevali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:56:36 by makevali          #+#    #+#             */
/*   Updated: 2025/12/22 12:11:28 by makevali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	in_bounds(t_game *gm, int x, int y)
{
	int	rowlen;

	if (y < 0 || y >= gm->map_h)
		return (0);
	rowlen = (int)strlen(gm->map[y]);
	if (x < 0 || x >= rowlen)
		return (0);
	return (1);
}

bool	is_wall(t_game *gm, int x, int y)
{
	char	c;
	int		row_width;

	if (x < 0 || y < 0 || y >= gm->map_h)
		return (1);
	row_width = (int)strlen(gm->map[y]);
	if (x >= row_width)
		return (1);
	c = gm->map[y][x];
	if (c == '1' || c == ' ' || c == 'D')
		return (1);
	return (0);
}

void	put_pixel(t_game *gm, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = gm->frame.data_img + y * gm->frame.line_len + x * (gm->frame.bpp / 8);
	*(unsigned int *)dst = color;
}

int	close_win(t_game *g)
{
	destroy_game(g, NULL);
	gc_free_all();
	return (0);
}

int	main_function(t_game *gm)
{
	gm->player.moving = false;
	move_player(gm);
	render_image(gm);
	draw_minimap(gm);
	draw_hands(gm);
	mlx_put_image_to_window(gm->mlx, gm->win, gm->frame.img, 0, 0);
	return (0);
}
