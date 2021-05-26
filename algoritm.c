/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:41:55 by ejina             #+#    #+#             */
/*   Updated: 2021/03/24 16:58:52 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algoritm.h"
#include "lines.h"

#define MIN(x, y) (x < y ? x : y)

int	print_square(t_map *map, t_square *coord)
{
	char		**str;
	int			i;
	int			j;

	str = map->field;
	i = coord->y - coord->size + 1;
	while (i <= coord->y)
	{
		j = coord->x - coord->size + 1;
		while (j <= coord->x)
		{
			str[i][j] = map->full;
			j++;
		}
		i++;
	}
	i = write(1, *map->field, map->height * (map->width + 1));
	return (i > 0 ? 0 : -1);
}

int	change_matrix(int **matr, t_map *map)
{
	int			i;
	int			j;
	t_square	*coord;

	if (!(coord = malloc(sizeof(t_square))))
		return (-1);
	coord->size = 0;
	i = -1;
	while (++i < map->height && (j = -1))
		while (++j < map->width)
		{
			if (matr[i][j] == 1 && i > 0 && j > 0)
				matr[i][j] = MIN(matr[i][j - 1],
					MIN(matr[i - 1][j], matr[i - 1][j - 1])) + 1;
			if (matr[i][j] > coord->size)
			{
				coord->size = matr[i][j];
				coord->x = j;
				coord->y = i;
			}
		}
	i = print_square(map, coord);
	free(coord);
	return (i);
}

int	matrix(t_map *map)
{
	int		**matr;
	int		i;
	int		j;

	i = 0;
	if (!(matr = get_2demiarr(map->height, map->width)))
		return (-1);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->field[i][j] == map->empty)
				matr[i][j] = 1;
			else
				matr[i][j] = 0;
			j++;
		}
		i++;
	}
	i = change_matrix(matr, map);
	free(matr);
	return (i);
}
