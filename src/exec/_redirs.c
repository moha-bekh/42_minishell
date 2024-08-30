/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 06:39:42 by moha              #+#    #+#             */
/*   Updated: 2024/08/30 04:28:16 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_swap_fd_redir_in(t_ppncmd cmd)
{
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	dup2((*cmd)->redirs.fd[0], STDIN_FILENO);
	close((*cmd)->redirs.fd[0]);
	return (_SUCCESS);
}

int	_swap_fd_redir_out(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCT);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCA);
	dup2((*cmd)->redirs.fd[1], STDOUT_FILENO);
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_read_from_pipe(t_ppncmd cmd)
{
	close((*cmd)->prev->redirs.pfd[1]);
	dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO);
	close((*cmd)->prev->redirs.pfd[0]);
	return (_SUCCESS);
}

int	_write_to_pipe(t_ppncmd cmd)
{
	close((*cmd)->redirs.pfd[0]);
	dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO);
	close((*cmd)->redirs.pfd[1]);
	return (_SUCCESS);
}

int	_exec_redirections(t_pdata data, t_ppncmd cmd)
{
	(void)data;
	if ((*cmd)->redirs.in_name && !(*cmd)->redirs.here_fd)
		_swap_fd_redir_in(cmd);
	else if ((*cmd)->redirs.here_fd && (*cmd)->redirs.here_name)
		_here_doc_proc(cmd);
	if ((*cmd)->redirs.out_name)
		_swap_fd_redir_out(cmd);
	if ((*cmd)->next && !(*cmd)->redirs.out_name)
		_write_to_pipe(cmd);
	if ((*cmd)->prev && !(*cmd)->redirs.in_name)
		_read_from_pipe(cmd);
	if ((*cmd)->redirs.here_name)
		unlink((*cmd)->redirs.here_name);
	return (_SUCCESS);
}
