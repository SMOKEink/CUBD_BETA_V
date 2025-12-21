#include "../../inc/cub3d.h"

typedef struct s_hand
{
	int	target_w;
	int	target_h;
	int	origin_x;
	int	origin_y;
}	t_hand;

static unsigned int	extract_hand_color(t_game *gm, t_hand *hand, int ix, int iy)
{
	int				tx;
	int				ty;
	unsigned int	col;

	tx = ix * gm->hand.w / hand->target_w;
	ty = iy * gm->hand.h / hand->target_h;
	col = texel_at(&gm->hand, tx, ty);
	if (!(col & 0x00FFFFFF))
		return (0);
	return (col);
}

static void	draw_scaled_hand(t_game *gm, t_hand *hand)
{
	int				px;
	int				py;
	int				ix;
	int				iy;
	unsigned int	col;

	iy = -1;
	while (++iy < hand->target_h)
	{
		py = hand->origin_y + iy;
		if (py < 0 || py >= HEIGHT)
			continue ;
		ix = -1;
		while (++ix < hand->target_w)
		{
			px = hand->origin_x + ix;
			if (px >= 0 && px < WIDTH)
			{
				col = extract_hand_color(gm, hand, ix, iy);
				if (col)
					put_pixel(gm, px, py, col);
			}
		}
	}
}

void	draw_hands(t_game *gm)
{
	t_hand	hand;
	int		bob;

	if (!gm->hand.img || !gm->hand.data)
		return ;
	if (gm->hand.h <= 0)
		gm->hand.h = 1;
	hand.target_h = (int)(HEIGHT * HAND_SCALE);
	hand.target_w = (int)((double)gm->hand.w * (double)hand.target_h
			/ (double)gm->hand.h);
	if (hand.target_w <= 0)
		hand.target_w = 1;
	if (!gm->keys.sprint)
		bob = (int)(sin(gm->hand_phase) * 20);
	else
		bob = (int)(sin(gm->hand_phase) * 40);
	hand.origin_x = (WIDTH - hand.target_w) / 2;
	hand.origin_y = HEIGHT - hand.target_h + (HEIGHT / 20) + bob;
	draw_scaled_hand(gm, &hand);
}
	// printf("-----------------------\nhand phase = %lf	bob = %d\n",gm->hand_phase, bob);
