/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:01:46 by aachata           #+#    #+#             */
/*   Updated: 2025/12/24 21:01:48 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	move_forward(t_game *gm, t_player *p)
{
	double	new_x;
	double	new_y;

	if (!gm->keys.sprint)
	{
		new_x = p->x + p->dir_x * MOVE_SPEED;
		new_y = p->y + p->dir_y * MOVE_SPEED;
	}
	else
	{
		new_x = p->x + p->dir_x * SPRINT_SPEED;
		new_y = p->y + p->dir_y * SPRINT_SPEED;
	}
	if (!collides_at(gm, new_x, p->y, 0.2))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y, 0.2))
		p->y = new_y;
}

static void	move_backward(t_game *gm, t_player *p)
{
	double	new_x;
	double	new_y;

	if (!gm->keys.sprint)
	{
		new_x = p->x - p->dir_x * MOVE_SPEED;
		new_y = p->y - p->dir_y * MOVE_SPEED;
	}
	else
	{
		new_x = p->x - p->dir_x * SPRINT_SPEED;
		new_y = p->y - p->dir_y * SPRINT_SPEED;
	}
	if (!collides_at(gm, new_x, p->y, 0.2))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y, 0.2))
		p->y = new_y;
}

static void	move_right(t_game *gm, t_player *p)
{
	double	new_x;
	double	new_y;

	if (!gm->keys.sprint)
	{
		new_x = p->x + p->dir_y * MOVE_SPEED;
		new_y = p->y - p->dir_x * MOVE_SPEED;
	}
	else
	{
		new_x = p->x + p->dir_y * SPRINT_SPEED;
		new_y = p->y - p->dir_x * SPRINT_SPEED;
	}
	if (!collides_at(gm, new_x, p->y, 0.2))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y, 0.2))
		p->y = new_y;
}

static void	move_left(t_game *gm, t_player *p)
{
	double	new_x;
	double	new_y;

	if (!gm->keys.sprint)
	{
		new_x = p->x - p->dir_y * MOVE_SPEED;
		new_y = p->y + p->dir_x * MOVE_SPEED;
	}
	else
	{
		new_x = p->x - p->dir_y * SPRINT_SPEED;
		new_y = p->y + p->dir_x * SPRINT_SPEED;
	}
	if (!collides_at(gm, new_x, p->y, 0.2))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y, 0.2))
		p->y = new_y;
}

void	move_player(t_game *gm)
{
	t_player	*p;

	p = &gm->player;
	if (gm->keys.up)
		move_forward(gm, p);
	if (gm->keys.down)
		move_backward(gm, p);
	if (gm->keys.right)
		move_right(gm, p);
	if (gm->keys.left)
		move_left(gm, p);
	if (gm->keys.rot_l || gm->keys.rot_r)
	{
		if (gm->keys.rot_r)
			rotate_player(p, -ROT_SPEED);
		else
			rotate_player(p, ROT_SPEED);
	}
}
