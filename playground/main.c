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

    // int out, _fd_stdout;

    // char str[13] = "Hello World!\n";


    // char *str2 = strdup(str + 6);

    // printf("%s", str + 6);
    // printf("%s", str2);

    // free(str2);

    // out = open("out", O_CREAT | O_RDWR | O_TRUNC, 0644);
    // if (out < 0)
    //     return (perror("open"), 1);

    // // CREATING A BACKUP OF STDOUT (COPY OF FD STDOUT)
    // _fd_stdout = dup(STDOUT_FILENO);

    // dprintf(STDOUT_FILENO, "Ya pas de Lezard!\n");

    // // REDIRECTING STDOUT TO OUT FILE
    // dup2(out, STDOUT_FILENO);
    // close(out);
    // dprintf(STDOUT_FILENO, "Ya un Lezard!\n");

    // // RESTORING STDOUT
    // dup2(_fd_stdout, STDOUT_FILENO);
    // close(_fd_stdout);
    // dprintf(STDOUT_FILENO, "dprintf: 0 Lezard!\n");
    
    return 0;
}

    // pid = fork();
    // if (pid < 0)
    //     return (perror("fork"), 1);
    // if (pid == 0)
    // {
    //     fd = open("out", O_CREAT | O_RDWR | O_TRUNC, 0644);
    //     if (fd < 0)
    //         return (perror("open"), 1);
    //     _stdout = dup(STDOUT_FILENO);
    //     dup2(fd, STDOUT_FILENO);
    //     close(fd);
    //     execl("/usr/bin/head", "head", "Makefile", NULL);
    //     return (perror("execl"), 1);
    // }
    // else
    // {
    //     waitpid(pid, &status, 0);
    //     if (WIFEXITED(status))
    //         printf("Child exited with status %d\n", WEXITSTATUS(status));
    //     else
    //         printf("Child exited abnormally\n");
    // }
