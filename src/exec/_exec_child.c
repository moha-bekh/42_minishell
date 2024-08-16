/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:53:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 20:54:17 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_redir_in(t_pcmd cmd)
{
	cmd->redir.fd[0] = open(cmd->redir.in_name, O_RDONLY);
	if (cmd->redir.fd[0] < 0)
		return (_EXT_OPEN);
	if (dup2(cmd->redir.fd[0], STDIN_FILENO) < 0)
		return (perror("dup2 in: "), _EXT_DUP2);
	close(cmd->redir.fd[0]);
	return (_SUCCESS);
}

int	_set_redir_out(t_pcmd cmd)
{
	if (cmd->redir.trunc)
		cmd->redir.fd[1] = open(cmd->redir.out_name, O_RDWR | O_CREAT | O_TRUNC,
				0644);
	else
		cmd->redir.fd[1] = open(cmd->redir.out_name,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (dup2(cmd->redir.fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2 out: "), _EXT_DUP2);
	close(cmd->redir.fd[1]);
	return (_SUCCESS);
}

int	_read_from_pipe(t_pcmd cmd)
{
	close(cmd->prev->redir.pfd[1]);
	if (dup2(cmd->prev->redir.pfd[0], STDIN_FILENO) < 0)
		return (perror("dup2 prev"), _EXT_DUP2);
	close(cmd->prev->redir.pfd[0]);
	return (_SUCCESS);
}

int	_write_to_pipe(t_pcmd cmd)
{
	close(cmd->redir.pfd[0]);
	if (dup2(cmd->redir.pfd[1], STDOUT_FILENO) < 0)
		return (perror("dup2 next"), _EXT_DUP2);
	close(cmd->redir.pfd[1]);
	return (_SUCCESS);
}

int	_exec_child_proc(t_pdata data, t_pcmd cmd)
{
	data->sa.sa_handler = child_hndl;
	if (cmd->prev)
		_read_from_pipe(cmd);
	if (cmd->next)
		_write_to_pipe(cmd);
	if (cmd->redir.in_name)
		_set_redir_in(cmd);
	if (cmd->redir.out_name)
		_set_redir_out(cmd);
	execve(cmd->cmd_path, cmd->cmd_arg, data->env.env);
	_exec_cmd_fail(data, cmd);
	return (_FAILURE);
}
