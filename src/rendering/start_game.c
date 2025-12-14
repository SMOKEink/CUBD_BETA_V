/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:10:04 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/03 21:50:33 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	start_game(t_game *gm)
{
    gm->mlx = mlx_init();
    if (!gm->mlx)
    {
        printf("Error\nMLX init failed\n");
        exit(1);
    }
    gm->win = mlx_new_window(gm->mlx, WIDTH, HEIGHT, "CUB3D");
    if (!gm->win)
    {
        printf("Error\nWindow creation failed\n");
        exit(1);
    }
    gm->frame.img = mlx_new_image(gm->mlx, WIDTH, HEIGHT);
    gm->frame.data_img = mlx_get_data_addr(gm->frame.img, &gm->frame.bpp, 
                                           &gm->frame.line_len, &gm->frame.endian);
    if (load_textures(gm))
    {
        printf("Error\nTexture load failed\n");
        exit(1); 
    }
    mlx_mouse_hide(gm->mlx, gm->win);
    mlx_loop_hook(gm->mlx, main_function, gm);
	mlx_hook(gm->win, 2, KeyPressMask, key_press, gm);
    mlx_hook(gm->win, 3, KeyReleaseMask, key_release, gm);
    mlx_hook(gm->win, 17, 0, close_win, gm); 
    mlx_hook(gm->win, MotionNotify, PointerMotionMask, mouse_move, gm);
    mlx_loop(gm->mlx);
}
