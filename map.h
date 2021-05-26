/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:37:35 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 21:03:01 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "cvector.h"

typedef struct	s_map
{
	char		**field;
	int			width;
	int			height;
	char		empty;
	char		obstacle;
	char		full;
}				t_map;

t_map			*get_map(char *path);
#endif
