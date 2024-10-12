/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_parent_wait_loop.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:31:00 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/12 02:09:04 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exec_parent_wait_loop(t_pdata data, t_ppbtree node)
{
	t_pncmd	cmd;

	cmd = (*node)->cmd_line->c_top;
	while (cmd)
	{
		if (_sig_parent_ign(data))
			return (_FAILURE);
		if (cmd->pid)
		{
				waitpid(cmd->pid, &data->_errno, 0);
			if (WIFEXITED(data->_errno))
				data->_errno = WEXITSTATUS(data->_errno);
			else if (WIFSIGNALED(data->_errno))
			data->_errno = WTERMSIG(data->_errno) + 128;
		}
		if (data->_errno == 130)
			write(1, "\n", 1);
		if (data->_errno == 131)
			write(1, "Quit (core dumped)\n", 19);
		if (_sig_parent_restore(data))
			return (_FAILURE);
		cmd = cmd->next;
	}
	return (_SUCCESS);
}
