#include "../libft/include/libft.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av, char **ev)
{
	char	**arr;

	arr = ft_split("*ou*", '*');
	printf("ptr: %p\n", arr);
	printf("arr[0]: %s\n", arr[0]);
	ft_free_arr(arr);
	arr = ft_split("*", '*');
	printf("ptr: %p\n", arr);
	printf("arr[0]: %s\n", arr[0]);
	return (0);
}
