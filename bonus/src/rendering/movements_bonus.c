/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makevali <makevali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:57:59 by makevali          #+#    #+#             */
/*   Updated: 2025/12/22 12:19:58 by makevali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

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
	if (!collides_at(gm, new_x, p->y))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y))
		p->y = new_y;
	p->moving = true;
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
	if (!collides_at(gm, new_x, p->y))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y))
		p->y = new_y;
	p->moving = true;
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
	if (!collides_at(gm, new_x, p->y))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y))
		p->y = new_y;
	p->moving = true;
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
	if (!collides_at(gm, new_x, p->y))
		p->x = new_x;
	if (!collides_at(gm, p->x, new_y))
		p->y = new_y;
	p->moving = true;
}

void	move_player(t_game *gm)
{
	if (gm->keys.up)
		move_forward(gm, &gm->player);
	if (gm->keys.down)
		move_backward(gm, &gm->player);
	if (gm->keys.right)
		move_right(gm, &gm->player);
	if (gm->keys.left)
		move_left(gm, &gm->player);
	if (gm->keys.rot_l || gm->keys.rot_r)
	{
		if (gm->keys.rot_r)
			rotate_player(&gm->player, -ROT_SPEED);
		else
			rotate_player(&gm->player, ROT_SPEED);
	}
	if (gm->player.moving)
		gm->hand_phase += 0.12;
	else
	{
		if (gm->hand_phase >= 40)
			gm->hand_phase = 40;
		gm->hand_phase *= 0.95;
	}
}
