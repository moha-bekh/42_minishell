/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:53:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 21:46:32 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_redir_in(t_pcmd *cmd)
{
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	if ((*cmd)->redirs.fd[0] < 0)
		return (_EXT_OPEN);
	if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->redirs.fd[0]);
	return (_SUCCESS);
}

int	_set_redir_out(t_pcmd *cmd)
{
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCT);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCA);
	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_read_from_pipe(t_pcmd *cmd)
{
	close((*cmd)->prev->redirs.pfd[1]);
	if (dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->prev->redirs.pfd[0]);
	return (_SUCCESS);
}

int	_write_to_pipe(t_pcmd *cmd)
{
	close((*cmd)->redirs.pfd[0]);
	if (dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->redirs.pfd[1]);
	return (_SUCCESS);
}

int	_exec_child_proc(t_pdata data, t_pcmd *cmd)
{
	data->s_sig.sa_handler = child_hndl;
	if ((*cmd)->prev)
		_read_from_pipe(cmd);
	if ((*cmd)->next)
		_write_to_pipe(cmd);
	if ((*cmd)->redirs.in_name)
		_set_redir_in(cmd);
	if ((*cmd)->redirs.out_name)
		_set_redir_out(cmd);
	close(data->args._stdin);
	close(data->args._stdout);
	execve((*cmd)->path, (*cmd)->args, data->args.env);
	if ((*cmd)->args && *(*cmd)->args)
		ft_dprintf(2, "bash: %s: command not found\n", (*cmd)->args[0]);
	_data_clear(data);
	exit(127);
	return (_FAILURE);
}
