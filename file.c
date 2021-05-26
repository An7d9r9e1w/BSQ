/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:43:58 by nnamor            #+#    #+#             */
/*   Updated: 2021/03/24 18:52:16 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "file.h"

t_cvector	*get_file_content(char *path)
{
	t_cvector	*content;
	char		buf[1024];
	int			fd;
	int			cnt;

	if (!path)
		fd = 0;
	else if ((fd = open(path, O_RDONLY)) < 3)
		return (0);
	if (!(content = create_cv()))
	{
		if (fd)
			close(fd);
		exit(-1);
	}
	while ((cnt = read(fd, buf, sizeof(buf))))
		if (cnt < 0 || write_cv(content, buf, cnt))
		{
			free_cv(content);
			return (0);
		}
	if (fd)
		close(fd);
	return (content);
}
