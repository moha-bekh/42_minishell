/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:20:38 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/12 02:18:30 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exec_child_proc(t_pdata data, t_pncmd cmd)
{
	if (_sig_child_dfl(data))
		return (_FAILURE);
	if (_exec_redirections(&cmd))
		_data_clear_exit(data, 1);
	if (!cmd->args)
		_data_clear_exit(data, 0);
	if (_is_builtin(data, cmd->args))
	{
		data->_errno = _exec_builtin(data, &cmd);
		_data_clear_exit(data, data->_errno);
	}
	else
	{
		if (_resolve_path(data, &cmd))
			return (_FAILURE);
		execve(cmd->path, cmd->args, data->args.env);
		if (cmd->args)
			_err_print(_ERR_NOT_FOUND, cmd->args[0], true, 127);
		_data_clear_exit(data, 127);
	}
	return (_SUCCESS);
}

int	_exec_process(t_pdata data, t_pncmd cmd)
{
	if (_xpd_line(data, &cmd->token) || _pars_args_line(data, &cmd, &cmd->token, true))
		return (_FAILURE);
	if (!cmd->next && !cmd->prev && _is_builtin(data, cmd->args))
		return (_exec_builtin_proc(data, &cmd));
	else
	{
		if (cmd->next && pipe(cmd->redirs.pfd) < 0)
			return (perror("pipe"), _FAILURE);
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (perror("fork"), _FAILURE);
		if (!cmd->pid && _exec_child_proc(data, cmd))
			return (_FAILURE);
		if (cmd->pid && cmd->prev)
		{
			close(cmd->prev->redirs.pfd[1]);
			close(cmd->prev->redirs.pfd[0]);
		}
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
	if (_exec_parent_wait_loop(data, node))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_exec_subshell(t_pdata data, t_ppbtree node)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), _FAILURE);
	if (!pid)
	{
		if (_exec(data, node))
			return (_FAILURE);
		_data_clear_exit(data, data->_errno);
	}
	else
	{
		waitpid(pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
		else if (WIFSIGNALED(data->_errno))
			data->_errno = WTERMSIG(data->_errno) + 128;
	}
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_ppbtree node)
{
	char	type;

	if (!*node)
		return (_SUCCESS);
	type = (*node)->token->x;
	if ((*node)->left)
		_exec(data, &(*node)->left);
	if (type == '(')
	{
		if (_exec_subshell(data, &(*node)->right))
			return (_FAILURE);
		return (_SUCCESS);
	}
	else if ((type == _AND && data->_errno) || (type == _OR && !data->_errno))
		return (_SUCCESS);
	else if (type != _AND && type != _OR && _exec_loop(data, node))
		return (_FAILURE);
	if ((*node)->right)
		_exec(data, &(*node)->right);
	return (_SUCCESS);
}
