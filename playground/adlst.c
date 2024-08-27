

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/minishell.h"


void	_dlst_pop_front(t_ppadlst dllst)
{
	t_pnlst	tmp;

	if (!*dllst)
		return ;
	tmp = (*dllst)->d_bot;
	if (--(*dllst)->d_size)
	{
		tmp = (*dllst)->d_top;
		(*dllst)->d_top = (*dllst)->d_top->next;
		(*dllst)->d_top->prev = NULL;
	}
	free(tmp->addr_1);
	free(tmp->addr_2);
	*tmp = (t_nlst){0};
	free(tmp);
	tmp = NULL;
	if (!(*dllst)->d_size)
	{
		(**dllst) = (t_adlst){0};
		free(*dllst);
		*dllst = NULL;
	}
}

typedef struct s_lst t_lst, *t_plst, **t_pplst;

int main(void)
{
    t_plst lst;

    t_padlst dlst;

    lst = NULL;
    dlst = NULL;
    _dlst_push_front(&dlst, strdup("1"), NULL, 1);


    return 0;
}
