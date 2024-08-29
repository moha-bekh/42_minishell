#include "../libft/include/libft.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av, char **ev)
{
	int _stdout_2 = dup(1);
	int fd = open("out", O_RDWR | O_CREAT | O_TRUNC, 0644);

	return (0);
}
