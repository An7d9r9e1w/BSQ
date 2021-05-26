/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:43:35 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 18:02:44 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cvector.h"

t_cvector	*create_cv(void)
{
	t_cvector	*vec;

	if (!(vec = malloc(sizeof(t_cvector))))
		return (NULL);
	vec->size = 1024;
	vec->count = 0;
	if (!(vec->arr = malloc(sizeof(char) * vec->size)))
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}

void		free_cv(t_cvector *vec)
{
	if (vec)
	{
		if (vec->arr)
			free(vec->arr);
		free(vec);
	}
}

int			realloc_cv(t_cvector *vec, unsigned int new_size)
{
	char			*arr;
	unsigned int	i;

	if (!new_size)
		return (1);
	if (!(arr = malloc(sizeof(char) * new_size)))
		return (2);
	if (new_size < vec->count)
		vec->count = new_size;
	i = 0;
	while (i < vec->count)
	{
		arr[i] = vec->arr[i];
		i++;
	}
	free(vec->arr);
	vec->arr = arr;
	vec->size = new_size;
	return (0);
}

int			write_cv(t_cvector *vec, char *str, unsigned int length)
{
	unsigned int	i;

	i = vec->size;
	while (vec->count + 1 + length > i)
		i <<= 1;
	if (i > vec->size)
		if (realloc_cv(vec, i))
			return (1);
	i = 0;
	while (i < length)
		vec->arr[vec->count++] = str[i++];
	vec->arr[vec->count] = 0;
	return (0);
}
