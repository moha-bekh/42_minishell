/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:36:01 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 17:17:24 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_wait_pids(t_pdata data, t_padlst cmd_line, t_pncmd limit)
{
	t_pncmd	tmp;

	(void)limit;
	tmp = cmd_line->c_top;
	while (tmp)
	{
		if (!tmp->args)
			return ;
		waitpid(tmp->pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
		if (tmp == limit)
			break ;
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
		if (pipe((*cmd)->redirs.pfd))
			return (perror("pipe: "), _EXT_PIPE);
	(*cmd)->pid = fork();
	if ((*cmd)->pid < 0)
		return (perror("fork: "), _EXT_FORK);
	if (!(*cmd)->pid)
	{
		if (_exec_child_proc(data, cmd))
			return (_FAILURE);
	}
	else
		_exec_parent_proc(cmd);
	return (_SUCCESS);
}

int	_exec_cmd_line(t_pdata data, t_ppbtree node)
{
	t_pncmd	tmp;

	(void)data;
	_pars_pipe_lines(node);
	tmp = (*node)->cmd_line->c_top;
	while (tmp)
	{
		_expand_line(&tmp->token);
		if (_pars_args_line(data, &tmp, &tmp->token, true))
			return (_FAILURE);
		// _expand_vars(data, &tmp);
		if (_is_builtin(data, tmp->args))
			_exec_builtin_proc(data, &tmp);
		else
		{
			_resolve_path(data, &tmp);
			if (_exec_proc(data, &tmp))
				return (_FAILURE);
		}
		tmp = tmp->next;
	}
	_wait_pids(data, (*node)->cmd_line, tmp);
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_ppbtree node)
{
	if (!*node)
		return (_SUCCESS);
	if ((*node)->left)
		_exec(data, &(*node)->left);
	if ((*node)->token->x == '(')
	{
		_cmd_push_back(&(*node)->cmd_line, (*node)->token);
		(*node)->cmd_line->c_top->pid = fork();
		if ((*node)->cmd_line->c_top->pid < 0)
		{
			data->_errno = (*node)->cmd_line->c_top->pid;
			return (perror("fork: "), _EXT_FORK);
		}
		if (!(*node)->cmd_line->c_top->pid)
			_exec(data, &(*node)->right);
		else
			waitpid((*node)->cmd_line->c_top->pid, &data->_errno, 0);
		return (_SUCCESS);
	}
	if ((*node)->token->x != _AND && (*node)->token->x != _OR)
		_exec_cmd_line(data, node);
	else
	{
		if ((*node)->token->x == _AND && data->_errno)
			return (_SUCCESS);
		else if ((*node)->token->x == _OR && !data->_errno)
			return (_SUCCESS);
	}
	if ((*node)->right)
		_exec(data, &(*node)->right);
	return (_SUCCESS);
}
