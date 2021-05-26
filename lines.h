/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:44:20 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 21:02:54 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINES_H
# define LINES_H

int		skip_line(char **str, int *size);
char	**get_2demcarr(char *str, int height, int width);
int		**get_2demiarr(int height, int width);
int		get_linelen(char *str);
#endif
