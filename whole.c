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

#ifndef FILE_H
# define FILE_H
# include "cvector.h"

t_cvector	*get_file_content(char *path);
#endif

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

#ifndef LINES_H
# define LINES_H

int		skip_line(char **str, int *size);
char	**get_2demcarr(char *str, int height, int width);
int		**get_2demiarr(int height, int width);
int		get_linelen(char *str);
#endif

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
