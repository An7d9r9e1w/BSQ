#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FEW_ARGS_ERROR "too few arguments\n"

int		get_strlen(char *str)
{
	int	len;
   
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	**get_2demarr(int height, int width)
{
	char	**arr;
	char	*tmp;

	if (height < 1 || width < 1)
		return (0);
	if (!(arr = malloc(sizeof(char*) * height +
		sizeof(char) * height * width)))
		return (0);
	tmp = (char*)(arr + height);
	for (int i = 0; i < height; i++)
		arr[i] = tmp + i * width;
	return (arr);
}

void	rand_fill_arr(char **arr, int rows, int colms, int dist)
{
	//srand(time(0));
	srand(clock());
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < colms; j++)
			arr[i][j] = (rand() % rows < dist) ? 'o' : '.';
		arr[i][colms] = '\n';
	}
}

int		main(int argc, char *argv[])
{
	char	**arr;
	int		x;
	int		y;
	int		dist;

	if (argc < 4)
	{
		write(2, FEW_ARGS_ERROR, sizeof(FEW_ARGS_ERROR));
		return (1);
	}
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	dist = atoi(argv[3]);
	if (!(arr = get_2demarr(y, x + 1)))
		return (1);
	write(1, argv[2], get_strlen(argv[2]));
	write(1, ".ox\n", 4);
	rand_fill_arr(arr, y, x, dist);
	dist = write(1, *arr, y * (x + 1));
	free(arr);
	return (dist < 0);
}
