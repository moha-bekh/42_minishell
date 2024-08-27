/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:10:13 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 16:38:35 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cmd_print_line(t_pncmd cmd)
{
	int	i;

	if (*cmd->args)
	{
		i = 0;
		while (cmd->args[i++])
			printf("\t %s\n", cmd->args[i]);
	}
	if (cmd->path)
		printf(" path: %s", cmd->path);
	else
		printf(" no path");
	if (cmd->redirs.in_name)
		printf("\t\tin_name: %s", cmd->redirs.in_name);
	if (cmd->redirs.here_name)
	{
		printf("\t\there_name: %s", cmd->redirs.here_name);
		i = -1;
		while (cmd->redirs.here_limit[++i])
			printf("\t\tlimiter: %d -> %s", i, cmd->redirs.here_limit[i]);
	}
	if (cmd->redirs.out_name)
		printf("\t\tout_name: %s", cmd->redirs.out_name);
	printf("\n");
}

void	_cmd_print_all(t_padlst dllst)
{
	t_pncmd	tmp;

	if (!dllst || !dllst->c_top)
		return ;
	tmp = dllst->c_top;
	while (tmp)
	{
		_cmd_print_line(tmp);
		tmp = tmp->next;
	}
}
