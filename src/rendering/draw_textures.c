#include "../../inc/cub3d.h"

unsigned int    texel_at(t_tex *t, int x, int y)
{
	char    *px;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= t->w)
		x = t->w - 1;
	if (y >= t->h)
		y = t->h - 1;
	px = t->data + y * t->line_len + x * (t->bpp / 8);
	return (*(unsigned int *)px);
}

char	map_cell(t_game *gm, int x, int y)
{
	int	len;

	if (y < 0 || y >= gm->map_h)
		return ('1');
	len = strlen(gm->map[y]);
	if (x < 0 || x >= len)
		return ('1');
	return (gm->map[y][x]);
}

t_tex	*choose_texture(t_game *gm, t_ray *ray)
{
	char    cell;

	cell = map_cell(gm, ray->map_x, ray->map_y);
	if (cell == 'D')
		return (&gm->door);
	if (cell == 'd')
		return (NULL);
	if (ray->hit_vertical)
	{
		if (ray->dir_x > 0)
			return (&gm->wall[TEX_W]);
		return (&gm->wall[TEX_E]);
	}
	if (ray->dir_y > 0)
		return (&gm->wall[TEX_N]);
	else
		return (&gm->wall[TEX_S]);
}

int hit_position(t_game *gm, t_tex *tex, t_ray *ray)
{
	int		tex_x;
	double	hit_point;

	if (ray->hit_vertical)
		hit_point = gm->player.y + ray->perp_dist * ray->dir_y;
	else
		hit_point = gm->player.x + ray->perp_dist * ray->dir_x;
	hit_point -= floor(hit_point);
	tex_x = (int)(hit_point * (double)tex->w);
	if (ray->hit_vertical && ray->dir_x > 0) //correct mirror textures
		tex_x = tex->w - tex_x;
	if (!ray->hit_vertical && ray->dir_y < 0)
		tex_x = tex->w - tex_x;
	return (tex_x);
}

void draw_slice(t_game *gm, t_slice *slice, t_tex *tex, t_ray *ray)
{
	int             y;
	unsigned int    color;
	double			real_start;

	slice->line_len = (int)(HEIGHT / ray->perp_dist);
	if (slice->line_len <= 0)
		slice->line_len = 1;
	slice->line_start = HEIGHT / 2 - slice->line_len / 2;
	slice->line_end = HEIGHT / 2 + slice->line_len / 2;
	if (slice->line_start < 0)
		slice->line_start = 0;
	if (slice->line_end >= HEIGHT)
		slice->line_end = HEIGHT - 1;
	slice->tex_step = (double)tex->h / (double)slice->line_len;
	real_start = HEIGHT / 2.0 - slice->line_len / 2.0;
	slice->tex_pos = (slice->line_start - real_start) * slice->tex_step;
	y = slice->line_start - 1;
	while (++y <= slice->line_end)
	{
		slice->tex_y = (int)slice->tex_pos;
		color = texel_at(tex, slice->tex_x, slice->tex_y);
		put_pixel(gm, slice->column, y, color);
		slice->tex_pos += slice->tex_step;
	}
}
