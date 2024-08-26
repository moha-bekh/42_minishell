// # include <readline/history.h>
// # include <readline/readline.h>
// # include <signal.h>
// # include <sys/stat.h>
// # include <sys/types.h>
// # include <sys/wait.h>

#include "../libft/include/libft.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av, char **ev)
{
    if (ac != 2)
    {
        printf("Usage: %s <wildcards>\n", av[0]);
        return (1);
    }
	char			*wildcards = av[1];
	char			**arr_cards;
	char			*expand_strings;
	char			*tmp;
	struct dirent	*entry;
	char			*name_cwd;
	DIR				*dir_cwd;
	int				i;

	arr_cards = ft_split(wildcards, '*');
	expand_strings = ft_strdup("");
	tmp = NULL;
	name_cwd = getcwd(NULL, 0);
	i = 0;
	while (arr_cards[i])
	{
		dir_cwd = opendir(name_cwd);
		entry = readdir(dir_cwd);
		while (entry)
		{
			if (strstr(entry->d_name, arr_cards[i]))
			{
				tmp = expand_strings;
				expand_strings = ft_strjoin(expand_strings, entry->d_name);
				free(tmp);
                tmp = expand_strings;
                expand_strings = ft_strjoin(expand_strings, " ");
                free(tmp);
				tmp = NULL;
			}
			entry = readdir(dir_cwd);
		}
		closedir(dir_cwd);
		i++;
	}
	if (expand_strings)
		printf("%s\n", expand_strings);
	free(expand_strings);
	ft_free_arr(arr_cards);
	free(name_cwd);
	return (0);
}
