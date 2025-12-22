/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:37:38 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/03 21:53:54 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static double	deg_to_rad(double deg)
{
	return (deg * (3.141592653589793 / 180.0));
}

static void	init_player_orientation(t_game *g, double angle_deg)
{
	double	angle_rad;

	angle_rad = deg_to_rad(angle_deg);
	g->player.dir_x = cos(angle_rad);
	g->player.dir_y = sin(angle_rad);
	g->player.plane_x = g->player.dir_y * 0.66;
	g->player.plane_y = -g->player.dir_x * 0.66;
}

void	merge_data(t_parse_data p_data, t_game *g)
{
	g->player.x = (double)p_data.p_x;
	g->player.y = (double)p_data.p_y;
	g->player.moving = false;
	init_player_orientation(g, p_data.angle);
	g->map_w = p_data.width;
	g->map_h = p_data.height;
	g->map = p_data.matrix;
	g->ceiling = p_data.assets->c_color;
	g->floor = p_data.assets->f_color;
	g->tex_path[TEX_N] = p_data.assets->north_wall;
	g->tex_path[TEX_E] = p_data.assets->east_wall;
	g->tex_path[TEX_S] = p_data.assets->south_wall;
	g->tex_path[TEX_W] = p_data.assets->west_wall;
	g->door_path = p_data.assets->door;
	g->hand_path = p_data.assets->hell_yeah;
	g->hand_phase = 0;
}
