// # include <readline/history.h>
// # include <readline/readline.h>
// # include <signal.h>
// # include <sys/stat.h>
// # include <sys/types.h>
// # include <sys/wait.h>

#include <stdio.h>
# include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av, char **ev)
{

    int _stdin, _stdout;

    _stdin = dup(0);
    _stdout = dup(1);
    
    return 0;
}
