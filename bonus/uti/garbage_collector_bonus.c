/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:26:18 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/30 20:37:11 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	*get_gc_fd(void)
{
	static int	fd = -1;

	return (&fd);
}

void	gc_set_fd(int fd)
{
	int	*ptr;

	ptr = get_gc_fd();
	*ptr = fd;
}

static t_garbage	**get_gc_head(void)
{
	static t_garbage	*head = NULL;

	return (&head);
}

void	*gc_malloc(size_t size)
{
	t_garbage	**head;
	void		*ptr;
	t_garbage	*node;

	head = get_gc_head();
	ptr = malloc(size);
	if (!ptr)
	{
		gc_free_all();
		exit(1);
		return (NULL);
	}
	node = malloc(sizeof(t_garbage));
	if (!node)
	{
		free(ptr);
		gc_free_all();
		exit(1);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}

void	gc_free_all(void)
{
	t_garbage	**head;
	t_garbage	*current;
	t_garbage	*next;
	int			*fd_ptr;

	fd_ptr = get_gc_fd();
	if (*fd_ptr >= 0)
	{
		close(*fd_ptr);
		*fd_ptr = -1;
	}
	head = get_gc_head();
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*head = NULL;
}
