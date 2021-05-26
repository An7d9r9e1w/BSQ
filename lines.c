/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:44:16 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 18:01:23 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lines.h"

int		get_linelen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

int		**get_2demiarr(int height, int width)
{
	int	**arr;
	int	*tmp;
	int	i;

	if (!(arr = malloc(sizeof(int*) * height +
		sizeof(int) * height * width)))
		return (0);
	tmp = (int*)(arr + height);
	i = -1;
	while (++i < height)
		arr[i] = tmp + i * width;
	return (arr);
}

char	**get_2demcarr(char *str, int height, int width)
{
	char	**arr;
	char	*tmp;
	int		i;
	int		j;

	if (!(arr = malloc(sizeof(char*) * height +
		sizeof(char) * height * width)))
		return (0);
	tmp = (char*)(arr + height);
	i = -1;
	while (++i < height)
		arr[i] = tmp + i * width;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			arr[i][j] = *str++;
	}
	return (arr);
}

int		skip_line(char **str, int *size)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = *str;
	while (len < *size && *tmp != '\n')
	{
		tmp++;
		len++;
	}
	*size -= len;
	*str = *tmp == '\n' ? ++tmp : tmp;
	return (len);
}
