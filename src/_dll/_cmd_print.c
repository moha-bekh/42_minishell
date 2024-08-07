/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:00:11 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 17:11:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cmd_print(u_padll dll)
{
	t_pcmd	tmp;
	int		i;

	if (!dll || !dll->c_top)
		return ;
	tmp = dll->c_top;
	if (tmp->cmd_arg)
	{
		printf("\n");
		printf("cmds: ");
		while (tmp)
		{
			i = -1;
			while (tmp->cmd_arg && tmp->cmd_arg[++i])
				printf(" %s ", tmp->cmd_arg[i]);
			if (tmp->cmd_path)
				printf(" cmd_path: %s\n", tmp->cmd_path);
			else
				printf(" no path\n");
			if (tmp->redir.in_name)
				printf("\t\tredir: %s\n", tmp->redir.in_name);
			if (tmp->redir.out_name)
				printf("\t\tredir: %s\n", tmp->redir.out_name);
			if (tmp->redir.here_name)
			{
				printf("\t\tredir: << %s\n", tmp->redir.here_name);
				printf("\t\tredir: %s\n", tmp->redir.here_limit);
			}
			tmp = tmp->next;
		}
		printf("\n");
	}
	return ;
}

// echo $USER > out $HOME | grep $USER || (cat < in 'salut $USER' && echo "hello $USER")