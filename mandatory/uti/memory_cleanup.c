/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makevali <makevali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:03:24 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/25 03:49:28 by makevali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map_lines(t_map_line *head)
{
	t_map_line	*node;
	t_map_line	*cup;

	node = head;
	while (node)
	{
		cup = node->next;
		free(node);
		node = cup;
	}
}
