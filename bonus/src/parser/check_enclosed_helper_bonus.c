/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enclosed_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:33:27 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/17 19:20:06 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	check_enclosed_helper2(char	**map, int x, int y, int in_spc)
{
	(void)in_spc;
	if (ft_strlen(map[y + 1]) < (size_t)(x + 1) && is_inner_char(map[y][x]))
		return (0);
	else if (ft_strlen(map[y + 1]) >= (size_t)(x + 1))
	{
		if (is_inner_char(map[y][x])
			&& (map[y + 1][x] != '1' && !is_inner_char(map[y + 1][x])))
			return (0);
	}
	return (1);
}

int	check_neighbors(char **map, int x, int y)
{
	if (y == 0 || is_whitespace(map[y - 1][x]))
		return (0);
	if (!map[y + 1] || is_whitespace(map[y + 1][x]))
		return (0);
	if (x == 0 || is_whitespace(map[y][x - 1]))
		return (0);
	if (is_whitespace(map[y][x + 1]))
		return (0);
	return (1);
}

int	is_whitespace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == '\0' || c == ' ');
}
