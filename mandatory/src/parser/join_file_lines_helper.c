/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_file_lines_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:07:39 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/17 19:10:02 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	join_file_lines_helper(char *buffer, int *map_started, int *map_gap)
{
	if (has_space_only(buffer))
	{
		if (*map_started)
			*map_gap = 1;
	}
	else
	{
		if (*map_gap)
			return (0);
		if (is_map(buffer))
			*map_started = 1;
	}
	return (1);
}
