/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:15:59 by ejina             #+#    #+#             */
/*   Updated: 2021/03/24 19:02:42 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "algoritm.h"

int	loop(int argc, char **argv)
{
	t_map	*map;
	int		status;
	int		i;

	i = -1;
	status = 0;
	while (++i < argc)
	{
		if ((map = get_map(argv[i])))
		{
			status = matrix(map);
			free(map->field);
			free(map);
			if (status)
				exit(-1);
		}
		else
			write(2, "map error\n", 10);
		if (i < argc - 1)
			write(1, "\n", 1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	**empty;
	char	*tmp;

	tmp = 0;
	empty = &tmp;
	if (argc < 2)
		loop(1, empty);
	else
		loop(argc - 1, argv + 1);
	return (0);
}
