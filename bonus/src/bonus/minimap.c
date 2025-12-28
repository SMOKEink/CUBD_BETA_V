/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makevali <makevali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:00:46 by aachata           #+#    #+#             */
/*   Updated: 2025/12/28 11:38:06 by makevali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	draw_player_marker(t_game *gm)
{
	int	y;
	int	x;
	int	px;
	int	py;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			px = MMAP_X + x;
			py = MMAP_Y + y;
			if (px >= 0 && py >= 0 && px < WIDTH && py < HEIGHT)
				put_pixel(gm, px, py, COL_PLAYER);
			x++;
		}
		y++;
	}
}

static void	draw_player_direction(t_game *gm, double p_dir_len)
{
	double	i;
	double	dir_x;
	double	dir_y;
	int		px;
	int		py;

	dir_x = gm->player.dir_x;
	dir_y = gm->player.dir_y;
	i = 0;
	while (i <= p_dir_len)
	{
		px = (int)(MMAP_X - dir_x * i);
		py = (int)(MMAP_Y + dir_y * i);
		if (px >= 0 && py >= 0 && px < WIDTH && py < HEIGHT)
			put_pixel(gm, px, py, COL_DIRECTION);
		i++;
	}
}

static void	draw_disk_pixel(t_game *gm, int px, int py, double cell_per_px)
{
	int		x;
	int		y;
	double	mx;
	double	my;
	char	cell;

	x = px - MMAP_X;
	y = py - MMAP_Y;
	mx = gm->player.x - x * cell_per_px;
	my = gm->player.y + y * cell_per_px;
	cell = map_cell(gm, (int)floor(mx), (int)floor(my));
	if (cell == '1')
		put_pixel(gm, px, py, COL_CUB);
	else if (cell == 'D')
		put_pixel(gm, px, py, COL_DOOR);
	else if (cell == 'd')
		put_pixel(gm, px, py, COL_OPENED_DOOR);
}

static void	draw_minimap_disk(t_game *gm, double cell_per_px)
{
	int		x;
	int		y;
	int		px;
	int		py;
	int		r_sq;

	r_sq = MMAP_R * MMAP_R; 
	y = -MMAP_R - 1;
	while (++y <= MMAP_R)
	{
		py = MMAP_Y + y;
		if (py < 0 || py >= HEIGHT)
			continue ;
		x = -MMAP_R - 1;
		while (++x <= MMAP_R)
		{
			if (x * x + y * y > r_sq)
				continue ;
			px = MMAP_X + x;
			if (px < 0 || px >= WIDTH)
				continue ;
			put_pixel(gm, px, py, COL_ROAD);
			draw_disk_pixel(gm, px, py, cell_per_px);
		}
	}
}

void	draw_minimap(t_game *gm)
{
	double	cell_per_px;
	double	p_dir_len;

	p_dir_len = 0.3 * MMAP_R;
	cell_per_px = 1.0 / MMAP_PIX_PER_CELL;
	draw_minimap_disk(gm, cell_per_px);
	draw_player_marker(gm);
	draw_player_direction(gm, p_dir_len);
}
