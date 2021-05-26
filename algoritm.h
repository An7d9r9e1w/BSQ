/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:34:39 by ejina             #+#    #+#             */
/*   Updated: 2021/03/24 21:03:59 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITM_H
# define ALGORITM_H
# include <unistd.h>
# include <stdlib.h>
# include "map.h"

typedef struct	s_square
{
	int x;
	int y;
	int size;
}				t_square;

int				matrix(t_map *map);
#endif
