/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:36:01 by moha              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/15 14:06:08 by mbekheir         ###   ########.fr       */
=======
/*   Updated: 2024/08/12 20:55:03 by mbekheir         ###   ########.fr       */
>>>>>>> parent of 2d7250c (PIPE 2024-08-13)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exec_cmd_fail(t_pdata data, t_pcmd cmd)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd_arg[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	_data_cleaner(data);
	exit(127);
	return (_FAILURE);
}

int	_exec_parent_proc(t_pdata data, t_pcmd cmd)
{
	waitpid(cmd->pid, &data->_errno, 0);
	if (WIFEXITED(data->_errno))
		data->_errno = WEXITSTATUS(data->_errno);
	if (cmd->prev)
	{
		close(cmd->prev->redir.pfd[0]);
		close(cmd->prev->redir.pfd[1]);
	}
	return (_SUCCESS);
}

int	_exec_proc(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	if (!data || !node)
		return (_FAILURE);
	// _resolve_path(data, node);
	tmp = node->cmd->c_top;
	while (tmp)
	{
		_expand(data);
		_pars_process(node, node->token);
		_resoleve_path_(data, tmp);
		if (tmp->built_in)
			data->_errno = _exec_builtin(data, tmp);
		else
		{
			if (tmp->next)
				if (pipe(tmp->redir.pfd))
					return (perror("pipe: "), _EXT_PIPE);
			tmp->pid = fork();
			if (tmp->pid < 0)
				return (perror("fork: "), _EXT_FORK);
			if (!tmp->pid)
			{
				if (_exec_child_proc(data, tmp))
					return (_FAILURE);
			}
			else
				_exec_parent_proc(data, tmp);
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_exec_cmd_line(t_pdata data, t_pbt_op tree)
{
	if (tree && !tree->root)
		_exec_proc(data, tree);
	else if (tree->root && tree == tree->root->left)
		_exec_proc(data, tree);
	else if (tree->root && tree == tree->root->right
		&& ((tree->root->type == _AND && data->_errno == 0)
			|| (tree->root->type == _OR && data->_errno != 0)))
		_exec_proc(data, tree);
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_pbt_op tree)
{
	if (!data || !tree)
		return (_FAILURE);
	if (tree->left)
		_exec(data, tree->left);
	if (tree->type != _AND && tree->type != _OR)
		_exec_cmd_line(data, tree);
	else
	{
		if (tree->type == _AND && data->_errno != 0)
			return (_SUCCESS);
		else if (tree->type == _OR && data->_errno == 0)
			return (_SUCCESS);
	}
	if (tree->right)
		_exec(data, tree->right);
	return (_SUCCESS);
}
