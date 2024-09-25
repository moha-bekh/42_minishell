/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:53:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/25 23:17:27 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_save_stdfds(t_pdata data)
{
	data->args._stdin = dup(STDIN_FILENO);
	data->args._stdout = dup(STDOUT_FILENO);
	return (_SUCCESS);
}

int	_restore_stdfds(t_pdata data)
{
	dup2(data->args._stdin, STDIN_FILENO);
	dup2(data->args._stdout, STDOUT_FILENO);
	return (_SUCCESS);
}

int	_exec_child_proc(t_pdata data, t_ppncmd cmd)
{
	_exec_redirections(cmd);
	execve((*cmd)->path, (*cmd)->args, data->args.env);
	if ((*cmd)->args)
		_err_print(_ERR_NOT_FOUND, (*cmd)->args[0], true, 127);
	_data_clear(data);
	exit(127);
	return (_FAILURE);
}
