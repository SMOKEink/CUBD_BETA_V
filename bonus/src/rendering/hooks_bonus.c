/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:02:59 by aachata           #+#    #+#             */
/*   Updated: 2025/12/24 21:03:13 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	key_press(int keycode, t_game *gm)
{
	if (keycode == XK_Escape)
		close_win(gm);
	else if (keycode == XK_w)
		gm->keys.up = 1;
	else if (keycode == XK_s)
		gm->keys.down = 1;
	else if (keycode == XK_a)
		gm->keys.left = 1;
	else if (keycode == XK_d)
		gm->keys.right = 1;
	else if (keycode == XK_Left)
		gm->keys.rot_l = 1;
	else if (keycode == XK_Right)
		gm->keys.rot_r = 1;
	else if (keycode == XK_e)
		toggle_door(gm);
	else if (keycode == XK_Shift_L)
		gm->keys.sprint = 1;
	return (0);
}

int	key_release(int keycode, t_game *gm)
{
	if (keycode == XK_w)
		gm->keys.up = 0;
	else if (keycode == XK_s)
		gm->keys.down = 0;
	else if (keycode == XK_a)
		gm->keys.left = 0;
	else if (keycode == XK_d)
		gm->keys.right = 0;
	else if (keycode == XK_Left)
		gm->keys.rot_l = 0;
	else if (keycode == XK_Right)
		gm->keys.rot_r = 0;
	else if (keycode == XK_Shift_L)
		gm->keys.sprint = 0;
	return (0);
}
