/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:37:16 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/22 02:49:16 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

char	*ft_strstr(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) == 0)
			return (s1 + i);
		i++;
	}
	return (NULL);
}

int	ft_charcount(char *s, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
