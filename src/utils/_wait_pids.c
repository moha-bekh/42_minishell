/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _wait_pids.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:28:27 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 12:28:34 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_wait_pids(t_pdata data, t_padlst cmd_line)
{
	t_pncmd	tmp;

	tmp = cmd_line->c_top;
	while (tmp)
	{
		waitpid(tmp->pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
		tmp = tmp->next;
	}
}
