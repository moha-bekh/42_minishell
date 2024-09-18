/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:36:01 by moha              #+#    #+#             */
/*   Updated: 2024/09/18 19:09:19 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	_wait_pids(t_pdata data, t_padlst cmd_line, t_pncmd limit)
// if (!tmp->args)
// 	return ;
// if (tmp == limit)
// 	break ;
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

int	_exec_parent_proc(t_ppncmd cmd)
{
	if ((*cmd)->prev)
	{
		close((*cmd)->prev->redirs.pfd[1]);
		close((*cmd)->prev->redirs.pfd[0]);
	}
	return (_SUCCESS);
}

int	_exec_proc(t_pdata data, t_ppncmd cmd)
{
	if ((*cmd)->next)
	{
		if (pipe((*cmd)->redirs.pfd) < 0)
			return (_err_print("bash: pipe failed", NULL, false, 1));
	}
	(*cmd)->pid = fork();
	if ((*cmd)->pid < 0)
		return (_err_print("bash: fork failed", NULL, false, 1));
	if (!(*cmd)->pid)
	{
		if (_exec_child_proc(data, cmd))
			return (_FAILURE);
	}
	else
		_exec_parent_proc(cmd);
	return (_SUCCESS);
}

int	_exec_process(t_pdata data, t_pncmd cmd)
{
	if (_xpd_line(data, &cmd->token))
		return (_FAILURE);
	if (_pars_args_line(data, &cmd, &cmd->token, true))
		return (_FAILURE);
	if (_is_builtin(data, cmd->args))
	{
		if (_exec_builtin_proc(data, &cmd))
			return (_FAILURE);
	}
	else
	{
		_resolve_path(data, &cmd);
		if (_exec_proc(data, &cmd))
			return (_FAILURE);
	}
	return (_SUCCESS);
}

int	_exec_cmd_line(t_pdata data, t_ppbtree node)
{
	_pars_pipe_lines(node);
	if (_cmd_foreach(data, (*node)->cmd_line->c_top, _exec_process, NULL))
		return (_FAILURE);
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
	if (((*node)->token->x == _AND && data->_errno) || ((*node)->token->x == _OR && !data->_errno))
		return (_SUCCESS);
	if ((*node)->token->x == '(')
	{
		if (_exec_subshell(data, &(*node)->right))
			return (_FAILURE);
		return (_SUCCESS);
	}
	if ((*node)->token->x != _AND && (*node)->token->x != _OR && _exec_cmd_line(data, node))
		return (_FAILURE);
	if ((*node)->right)
		_exec(data, &(*node)->right);
	return (_SUCCESS);
}
