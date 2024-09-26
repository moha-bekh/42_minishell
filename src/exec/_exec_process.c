/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:36:01 by moha              #+#    #+#             */
/*   Updated: 2024/09/26 12:32:08 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exec_process(t_pdata data, t_pncmd cmd)
{
	if (_xpd_line(data, &cmd->token))
		return (_FAILURE);
	if (_pars_args_line(data, &cmd, &cmd->token, true))
		return (_FAILURE);
	if (!cmd->next && !cmd->prev && _is_builtin(data, cmd->args))
	{
		if (_exec_builtin_proc(data, &cmd))
			return (_FAILURE);
	}
	else
	{
		if (_exec_proc(data, &cmd))
			return (_FAILURE);
	}
	return (_SUCCESS);
}

int	_exec_loop(t_pdata data, t_ppbtree node)
{
	t_pncmd	cmd;

	if (_pars_pipe_lines(node))
		return (_FAILURE);
	cmd = (*node)->cmd_line->c_top;
	while (cmd)
	{
		if (_exec_process(data, cmd))
			return (_FAILURE);
		cmd = cmd->next;
	}
	_wait_pids(data, (*node)->cmd_line);
	return (_SUCCESS);
}

int	_exec_subshell(t_pdata data, t_ppbtree node)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (_err_print("bash: fork failed", NULL, false, 1));
	if (!pid)
	{
		if (_exec(data, node))
			return (_FAILURE);
		_data_clear(data);
		exit(data->_errno);
	}
	else
	{
		waitpid(pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
	}
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_ppbtree node)
{
	if (!*node)
		return (_SUCCESS);
	if ((*node)->left)
		_exec(data, &(*node)->left);
	if (((*node)->token->x == _AND && data->_errno) || ((*node)->token->x == _OR
			&& !data->_errno))
		return (_SUCCESS);
	if ((*node)->token->x == '(')
	{
		if (_exec_subshell(data, &(*node)->right))
			return (_FAILURE);
		return (_SUCCESS);
	}
	if ((*node)->token->x != _AND && (*node)->token->x != _OR
		&& _exec_loop(data, node))
		return (_FAILURE);
	if ((*node)->right)
		_exec(data, &(*node)->right);
	return (_SUCCESS);
}
