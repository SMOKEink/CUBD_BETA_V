/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:59:26 by aachata           #+#    #+#             */
/*   Updated: 2025/12/30 19:24:08 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

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

static void	protect_macros(void)
{
	if (HEIGHT < 0 || WIDTH < 0 || MOVE_SPEED < 0 || SPRINT_SPEED < 0
		|| TEX_WALL_COUNT != 4 || MOUSE_ROT_SPEED < 0 || HAND_SCALE < 0
		|| MMAP_PIX_PER_CELL < 0)
	{
		printf("Error\nDON'T USE NEGATIVE NUMBERS !!!\n");
		gc_free_all();
		exit(1);
	}
}

int	start_game(t_game *gm)
{
	protect_macros();
	gm->mlx = mlx_init();
	if (!gm->mlx)
		return (printf("Error\nMlx init failed\n"));
	gm->win = mlx_new_window(gm->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!gm->win)
		return (printf("Error\nWindow creation failed\n"));
	gm->frame.img = mlx_new_image(gm->mlx, WIDTH, HEIGHT);
	gm->frame.data_img = mlx_get_data_addr(gm->frame.img, &gm->frame.bpp,
			&gm->frame.line_len, &gm->frame.endian);
	if (load_textures(gm))
		return (printf("Error\nTexture load failed\n"));
	mlx_mouse_hide(gm->mlx, gm->win);
	mlx_loop_hook(gm->mlx, main_function, gm);
	mlx_hook(gm->win, KeyPress, KeyPressMask, key_press, gm);
	mlx_hook(gm->win, KeyRelease, KeyReleaseMask, key_release, gm);
	mlx_hook(gm->win, DestroyNotify, 0, close_win, gm);
	mlx_hook(gm->win, MotionNotify, PointerMotionMask, mouse_move, gm);
	mlx_loop(gm->mlx);
	return (0);
}
