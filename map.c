/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:47:11 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 21:18:13 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "map.h"
#include "file.h"
#include "lines.h"

int		get_field(t_map *map, char *str, int size)
{
	skip_line(&str, &size);
	if (!(map->field = get_2demcarr(str, map->height, map->width + 1)))
		return (-1);
	return (0);
}

int		check_field(t_map *map, char *str, int size)
{
	int	curlen;
	int	len;
	int count;

	skip_line(&str, &size);
	if (!(len = get_linelen(str)))
		return (-1);
	count = 0;
	while (*str)
	{
		curlen = 0;
		while (*str && *str != '\n')
		{
			if (*str != map->empty && *str != map->obstacle)
				return (-1);
			str++;
			curlen++;
		}
		if (curlen != len || !*str)
			return (-1);
		count++;
		str++;
	}
	map->width = len;
	return (-(map->height != count));
}

int		get_map_attr(t_map *map, char *str, int size)
{
	int	len;
	int	i;
	int	height;

	len = 0;
	while (len < size && str[len] != '\n')
		len++;
	if (len < 4)
		return (-1);
	height = 0;
	i = 0;
	while ((i < len - 3) && str[i] >= '0' && str[i] <= '9')
		height = height * 10 + str[i++] - '0';
	if ((len - i) != 3 || !height || str[i] == str[i + 1] ||
		str[i] == str[i + 2] || str[i + 1] == str[i + 2] ||
		!(str[i] > 31 && str[i] < 127 &&
		str[i + 1] > 31 && str[i + 1] < 127 &&
		str[i + 2] > 31 && str[i + 2] < 127))
		return (-1);
	map->height = height;
	map->empty = str[i];
	map->obstacle = str[i + 1];
	map->full = str[i + 2];
	return (0);
}

int		fill_map(t_map **map, char *str, int size)
{
	if (get_map_attr(*map, str, size) ||
		check_field(*map, str, size))
		return (1);
	else if (get_field(*map, str, size))
		return (-1);
	return (0);
}

t_map	*get_map(char *path)
{
	t_cvector	*content;
	t_map		*map;
	int			status;

	content = 0;
	status = 0;
	map = 0;
	if ((content = get_file_content(path)))
	{
		if ((map = malloc(sizeof(t_map))))
		{
			if ((status = fill_map(&map, content->arr, content->count)))
				free(map);
		}
		else
			status = -1;
	}
	if (content)
		free_cv(content);
	if (status < 0)
		exit(status);
	else
		return (status ? 0 : map);
}
