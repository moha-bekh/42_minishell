/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:36:01 by moha              #+#    #+#             */
/*   Updated: 2024/08/08 16:49:30 by mbekheir         ###   ########.fr       */
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

int	_exec_builtin(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (!ft_strcmp(cmd->cmd_arg[0], "pwd"))
		return (_pwd());
	else if (!ft_strcmp(cmd->cmd_arg[0], "echo"))
		return (_echo(data, cmd->cmd_arg));
	// else if (!ft_strcmp(cmd->cmd_arg[0], "cd"))
	// 	_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd_arg[0], "export"))
		return (_export(data, cmd->cmd_arg));
	else if (!ft_strcmp(cmd->cmd_arg[0], "unset"))
		return (_unset(data, cmd->cmd_arg));
	else if (!ft_strcmp(cmd->cmd_arg[0], "env"))
		return (_env(data, cmd->cmd_arg));
	else if (!ft_strcmp(cmd->cmd_arg[0], "exit"))
		return (_exit_(data, cmd->cmd_arg));
	return (_SUCCESS);
}

int	_set_prev_pipe(t_pcmd cmd)
{
	close(cmd->prev->redir.pfd[1]);
	if (dup2(cmd->prev->redir.pfd[0], STDIN_FILENO) < 0)
		return (_EXT_DUP2);
	close(cmd->prev->redir.pfd[0]);
	return (_SUCCESS);
}

int	_set_next_pipe(t_pcmd cmd)
{
	if (pipe(cmd->redir.pfd) < 0)
		return (_EXT_PIPE);
	close(cmd->redir.pfd[0]);
	return (_SUCCESS);
}

int	_set_redir_in(t_pcmd cmd)
{
	// printf("infile: %s\n", cmd->redir.in_name);
	cmd->redir.fd[0] = open(cmd->redir.in_name, O_RDONLY);
	if (cmd->redir.fd[0] < 0)
		return (_EXT_OPEN);
	printf("fd: %d\n", cmd->redir.fd[0]);
	if (dup2(cmd->redir.fd[0], STDIN_FILENO) < 0)
		return (_EXT_DUP2);
	close(cmd->redir.fd[0]);
	return (_SUCCESS);
}

int	_set_redir_out(t_pcmd cmd)
{
	if (cmd->redir.trunc)
		cmd->redir.fd[1] = open(cmd->redir.out_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		cmd->redir.fd[1] = open(cmd->redir.out_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	printf("fd: %d\n", cmd->redir.fd[1]);
	return (_SUCCESS);
}

int	_exec_child_process(t_pdata data, t_pcmd cmd)
{
	// if (cmd->prev && !cmd->redir.in_name)
	// 	_set_prev_pipe(cmd);
	printf("in_name: %s\n", cmd->redir.in_name);
	if (cmd->redir.in_name)
		_set_redir_in(cmd);
	// if (cmd->next && !cmd->redir.out_name)
	// {
	// 	if (dup2(cmd->redir.pfd[1], STDOUT_FILENO) < 0)
	// 		return (_EXT_DUP2);
	// 	close(cmd->redir.pfd[1]);
	// }
	printf("out_name: %s\n", cmd->redir.out_name);
	if (cmd->redir.out_name)
		_set_redir_out(cmd);
	execve(cmd->cmd_path, cmd->cmd_arg, data->env.env);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd_arg[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
	return (_FAILURE);
}

int	_exec_proc(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	// int		i;
	if (!data || !node)
		return (_FAILURE);
	_resolve_path(data, node);
	tmp = node->cmd->c_top;
	while (tmp)
	{
		// if (tmp->cmd_arg)
		// {
		// 	i = -1;
		// 	printf("Args: ");
		// 	while (tmp->cmd_arg[++i])
		// 		printf("%s ", tmp->cmd_arg[i]);
		// 	printf("\n");
		// }
		if (tmp->built_in)
		{
			data->_errno = _exec_builtin(data, tmp);
			tmp->status = data->_errno;
			node->status = data->_errno;
		}
		else
		{
			// if (tmp->next && !tmp->redir.out_name)
			// 	_set_next_pipe(tmp);
			tmp->pid = fork();
			if (tmp->pid < 0)
				return (_EXT_FORK);
			else if (tmp->pid == 0)
				_exec_child_process(data, tmp);
			else
			{
				waitpid(tmp->pid, &tmp->status, 0);
				if (WIFEXITED(tmp->status))
				{
					data->_errno = WEXITSTATUS(tmp->status);
					node->status = data->_errno;
					// printf("Exit status: %d\n", data->_errno);
				}
				// close(tmp->redir.pfd[1]);
			}
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
	{
		_exec_proc(data, tree);
		tree->root->status = tree->status;
	}
	else if (tree->root && tree == tree->root->right
		&& ((tree->root->type == _AND && tree->root->status == 0)
			|| (tree->root->type == _OR && tree->root->status != 0)))
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
		if (tree->type == _AND && tree->status != 0)
			return (_SUCCESS);
		else if (tree->type == _OR && tree->status == 0)
			return (_SUCCESS);
	}
	if (tree->right)
		_exec(data, tree->right);
	return (_SUCCESS);
}
