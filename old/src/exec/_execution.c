/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:53:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/31 15:39:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_builtin(t_pdata data, char *str)
{
	int	i;

	if (!data || !str)
		return (_ERROR);
	i = 0;
	while (data->built_in[i])
	{
		if (!ft_strcmp(data->built_in[i], str))
			return (_IS);
		i++;
	}
	return (_NOT);
}

int	_resolve_path(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	if (!data || !node)
		return (_ERROR);
	tmp = node->cmd->c_top;
	while (tmp)
	{
		if (tmp->cmd_a && _is_builtin(data, tmp->cmd_a[0]))
		{
			tmp->built_in = true;
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->cmd_a)
			_check_access(data, tmp);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_set_prev_pipe(t_pdata data, t_pcmd tmp)
{
	if (!data || !tmp)
		return (_ERROR);
	close(tmp->prev->redir.pfd[1]);
	if (dup2(tmp->prev->redir.pfd[0], STDIN_FILENO) < 0)
		return (_EXT_PIPE);
	return (_SUCCESS);
}

int	_set_next_pipe(t_pdata data, t_pcmd tmp)
{
	if (!data || !tmp)
		return (_ERROR);
	if (pipe(tmp->redir.pfd) < 0)
		return (_EXT_PIPE);
	close(tmp->redir.pfd[0]);
	return (_SUCCESS);
}

int	_exec_redir_int(t_pdata data, t_pcmd tmp)
{
	if (!data || !tmp)
		return (_ERROR);
	if (tmp->redir.in_name)
	{
		tmp->redir.fd[0] = open(tmp->redir.in_name, O_RDONLY);
		if (tmp->redir.fd[0] < 0)
		{
			tmp->redir.fd[0] = open("/dev/null", O_RDONLY);
			if (tmp->redir.fd[0] < 0)
				return (_EXT_OPEN);
		}
	}
	return (_SUCCESS);
}

int	_exec_redir_out(t_pdata data, t_pcmd tmp)
{
	if (!data || !tmp)
		return (_ERROR);
	if (tmp->redir.out_name)
	{
		if (tmp->redir.trunc)
			tmp->redir.fd[1] = open(tmp->redir.out_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			tmp->redir.fd[1] = open(tmp->redir.out_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->redir.fd[1] < 0)
			return (_EXT_OPEN);
	}
	return (_SUCCESS);
}

int	_execution_child(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	return (_SUCCESS);
}

int	_exec_child_process(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (cmd->prev)
		_set_prev_pipe(data, cmd->prev);
	else
		_exec_redir_int(data, cmd);
	if (cmd->next)
	{
		if (dup2(cmd->redir.pfd[1], STDOUT_FILENO) < 0)
			return (_EXT_PIPE);
		close(cmd->redir.pfd[1]);
	}
	else
		_exec_redir_out(data, cmd);
	_execution_child(data, cmd);
	return (_SUCCESS);
}

int _exec_builtin(t_pdata data , t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (!ft_strcmp(cmd->cmd_a[0], "pwd"))
		_pwd(data);
	// else if (!ft_strcmp(cmd->cmd_a[0], "echo"))
	// 	_echo(data, cmd);
	// else if (!ft_strcmp(cmd->cmd_a[0], "cd"))
	// 	_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd_a[0], "export"))
		_export(data, cmd->cmd_a);
	else if (!ft_strcmp(cmd->cmd_a[0], "unset"))
		_unset(data, cmd->cmd_a);
	else if (!ft_strcmp(cmd->cmd_a[0], "env"))
		_env(data, cmd->cmd_a);
	else if (!ft_strcmp(cmd->cmd_a[0], "exit"))
		_exit_(data, cmd->cmd_a);
	return (_SUCCESS);
}

int	_exec_process(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	if (!data || !node)
		return (_ERROR);
	tmp = node->cmd->c_top;
	while (tmp)
	{
		if (tmp->built_in)
			_exec_builtin(data, tmp);
		else
		{
			if (tmp->next)
				_set_next_pipe(data, tmp);
			tmp->pid = fork();
			if (tmp->pid < 0)
				return (_ERROR);
			else if (tmp->pid == 0)
				_exec_child_process(data, tmp);
			else
				waitpid(tmp->pid, &tmp->status, 0);
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_execution(t_pdata data, t_pbt_op tree)
{
	if (!data || !tree)
		return (_ERROR);
	if (!tree->root || (tree->root && tree->root->cmd->c_bot->status))
	{
		_resolve_path(data, tree);
		_exec_process(data, tree);
	}
	if (tree->left)
		_execution(data, tree->left);
	if (tree->right)
		_execution(data, tree->right);
	return (_SUCCESS);
}
