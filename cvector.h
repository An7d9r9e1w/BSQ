/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:43:48 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 21:02:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CVECTOR_H
# define CVECTOR_H

typedef struct	s_cvector
{
	char			*arr;
	unsigned int	size;
	unsigned int	count;
}				t_cvector;

t_cvector		*create_cv();
void			free_cv(t_cvector *vec);
int				write_cv(t_cvector *vec, char *str, unsigned int length);
#endif
