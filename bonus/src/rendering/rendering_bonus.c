#include "../../inc/cub3d_bonus.h"

void    ceil_and_floor(t_game *gm)
{
	int x;
	int y;

	y = 0;
	while (y <= HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(gm, x, y, gm->ceiling);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(gm, x, y, gm->floor);
			x++;
		}
		y++;
	}
}

static void init_ray(t_game *gm, int x, t_ray *ray)
{
	ray->cam_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = gm->player.dir_x + gm->player.plane_x * ray->cam_x;
	ray->dir_y = gm->player.dir_y + gm->player.plane_y * ray->cam_x;
	ray->map_x = (int)gm->player.x;
	ray->map_y = (int)gm->player.y;
	if (ray->dir_x != 0)
		ray->delta_x = fabs(1 / ray->dir_x);
	else
		ray->delta_x = INFINITY;
	if (ray->dir_y != 0)
		ray->delta_y = fabs(1 / ray->dir_y);
	else
		ray->delta_y = INFINITY;
}

static void init_first_steps(t_game *gm, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (gm->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1 - gm->player.x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (gm->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1 - gm->player.y) * ray->delta_y;
	}
}

static void dda_loop(t_game *gm, t_ray *ray)
{
	bool    hit;

	hit = false;
	while (!hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->map_x += ray->step_x;
			ray->side_x += ray->delta_x;
			ray->hit_vertical = true;
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->side_y += ray->delta_y;
			ray->hit_vertical = false;
		}
		if (is_wall(gm, ray->map_x, ray->map_y))
			hit = true;
	}
	if (ray->hit_vertical)
		ray->perp_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_y - ray->delta_y;
}

void    render_image(t_game *gm)
{
	int     x;
	t_ray   ray;
	t_tex   *tex;
	t_slice slice;

	ceil_and_floor(gm);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(gm, x, &ray);
		init_first_steps(gm, &ray);
		dda_loop(gm, &ray);
		tex = choose_texture(gm, &ray);
		if (tex)
		{
			slice.column = x;
			slice.tex_x = hit_position(gm, tex, &ray);
			draw_slice(gm, &slice, tex, &ray);
		}
		x++;
	}
}

