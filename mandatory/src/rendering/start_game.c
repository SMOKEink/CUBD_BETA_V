/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachata <aachata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:02:04 by aachata           #+#    #+#             */
/*   Updated: 2025/12/24 21:02:06 by aachata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	start_game(t_game *gm)
{
	gm->mlx = mlx_init();
	if (!gm->mlx)
		return (printf("Error\nMLX init failed\n"));
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
	mlx_hook(gm->win, 2, KeyPressMask, key_press, gm);
	mlx_hook(gm->win, 3, KeyReleaseMask, key_release, gm);
	mlx_hook(gm->win, 17, 0, close_win, gm);
	mlx_hook(gm->win, MotionNotify, PointerMotionMask, mouse_move, gm);
	mlx_loop(gm->mlx);
	return (0);
}
