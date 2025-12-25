/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:00:41 by aachata           #+#    #+#             */
/*   Updated: 2025/12/24 21:00:43 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	consider_cell(t_game *gm, t_door *best, int tx, int ty)
{
	char	cell;
	double	vx;
	double	vy;
	double	dist;
	double	dot;

	cell = gm->map[ty][tx];
	if (cell != 'D' && cell != 'd')
		return (0);
	best->cx = tx + 0.5;
	best->cy = ty + 0.5;
	vx = best->cx - gm->player.x;
	vy = best->cy - gm->player.y;
	dist = sqrt(vx * vx + vy * vy);
	if (dist < 0.7)
		return (0);
	dot = (vx / dist) * gm->player.dir_x + (vy / dist) * gm->player.dir_y;
	if (dot < 0.7)
		return (0);
	if (dist < best->dist)
		return (best->dist = dist, best->x = tx, best->y = ty, 0);
	return (0);
}

static void	scan_neighbours(t_game *gm, t_door *best, int p_x, int p_y)
{
	int	ix;
	int	iy;
	int	tx;
	int	ty;

	p_x = (int)gm->player.x;
	p_y = (int)gm->player.y;
	iy = -1;
	while (iy <= 1)
	{
		ty = p_y + iy;
		ix = -1;
		while (ix <= 1)
		{
			tx = p_x + ix;
			if (in_bounds(gm, tx, ty))
				consider_cell(gm, best, tx, ty);
			ix++;
		}
		iy++;
	}
}

static void	apply_toggle(t_game *gm, t_door *best)
{
	char	*cell;

	if (best->x == -1 || best->dist > 1.1)
		return ;
	cell = &gm->map[best->y][best->x];
	if (*cell == 'd')
		*cell = 'D';
	else if (*cell == 'D')
		*cell = 'd';
}

void	toggle_door(t_game *gm)
{
	t_door	best;
	int		p_x;
	int		p_y;

	p_x = 0;
	p_y = 0;
	best.x = -1;
	best.y = -1;
	best.dist = 2.0;
	scan_neighbours(gm, &best, p_x, p_y);
	apply_toggle(gm, &best);
}
