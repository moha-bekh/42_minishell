/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:36:01 by moha              #+#    #+#             */
/*   Updated: 2024/08/06 09:18:06 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exec_builtin(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (!ft_strcmp(cmd->cmd_arg[0], "pwd"))
		_pwd(data);
	// else if (!ft_strcmp(cmd->cmd_arg[0], "echo"))
	// 	_echo(data, cmd);
	// else if (!ft_strcmp(cmd->cmd_arg[0], "cd"))
	// 	_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd_arg[0], "export"))
		_export(data, cmd->cmd_arg);
	else if (!ft_strcmp(cmd->cmd_arg[0], "unset"))
		_unset(data, cmd->cmd_arg);
	else if (!ft_strcmp(cmd->cmd_arg[0], "env"))
		_env(data, cmd->cmd_arg);
	else if (!ft_strcmp(cmd->cmd_arg[0], "exit"))
		_exit_(data, cmd->cmd_arg);
	return (_SUCCESS);
}

int	_exec_process(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	if (!data || !node)
		return (_FAILURE);
	// _resolve_path(data, node);
	tmp = node->cmd->c_top;
	while (tmp)
	{
		if (tmp->built_in)
			_exec_builtin(data, tmp);
		// else
		// {
		// 	if (tmp->next)
		// 		_set_next_pipe(data, tmp);
		// 	tmp->pid = fork();
		// 	if (tmp->pid < 0)
		// 		return (_ERROR);
		// 	else if (tmp->pid == 0)
		// 		_exec_child_process(data, tmp);
		// 	else
		// 		waitpid(tmp->pid, &tmp->status, 0);
		// }
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_pbt_op tree)
{
	if (!data || !tree)
		return (_FAILURE);
	if (tree->left)
		_exec(data, tree->left);
	if (tree->type != _AND && tree->type != _OR)
	{
		if (tree == tree->root->left)
		{
			_exec_process(data, tree);
			if (tree->root && tree->cmd->c_bot->status == 1)
				tree->root->status ^= 1;
		}
		else if ((tree->root && tree->root->type == _AND
				&& tree->root->status == 1) || (tree->root
				&& tree->root->type == _OR && tree->root->status == 0))
		{
			_exec_process(data, tree);
			if (tree->root && tree->cmd->c_bot->status == 0)
				tree->root->status ^= 1;
		}
	}
	else
	{
		if (tree->left && tree->left->type == _AND && tree->left->status == 0)
			return (_SUCCESS);
		else if (tree->left && tree->left->type == _OR
			&& tree->left->status == 1)
			return (_SUCCESS);
	}
	if (tree->right)
		_exec(data, tree->right);
	return (_SUCCESS);
}
