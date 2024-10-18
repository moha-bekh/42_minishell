/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 06:39:42 by moha              #+#    #+#             */
/*   Updated: 2024/10/18 15:36:28 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_swap_fd_redir_in(t_ppncmd cmd)
{
	if ((*cmd)->redirs.in_name[0] == '$')
		return (_err_print(_ERR_AMBIGOUS, (*cmd)->redirs.in_name, true, 1));
	if (access((*cmd)->redirs.in_name, F_OK))
		return (_err_print(_ERR_NO_FILE, (*cmd)->redirs.in_name, true, 1));
	else if (access((*cmd)->redirs.in_name, R_OK))
		return (_err_print(_ERR_PERM, (*cmd)->redirs.in_name, true, 1));
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	if ((*cmd)->redirs.fd[0] < 0)
		return (perror("open"), _FAILURE);
	if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->redirs.fd[0]);
	return (_SUCCESS);
}

int	_swap_fd_redir_out(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_name[0] == '$')
		return (_err_print(_ERR_AMBIGOUS, (*cmd)->redirs.out_name, true, 1));
	if (access((*cmd)->redirs.out_name, W_OK))
		return (_err_print(_ERR_PERM, (*cmd)->redirs.out_name, true, 1));
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*cmd)->redirs.fd[1] < 0)
		return (perror("open"), _FAILURE);
	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_read_from_pipe(t_ppncmd cmd)
{
	close((*cmd)->prev->redirs.pfd[1]);
	(*cmd)->prev->redirs.pfd[1] = -1;
	if (dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->prev->redirs.pfd[0]);
	(*cmd)->prev->redirs.pfd[0] = -1;
	return (_SUCCESS);
}

int	_write_to_pipe(t_ppncmd cmd)
{
	close((*cmd)->redirs.pfd[0]);
	(*cmd)->redirs.pfd[0] = -1;
	if (dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->redirs.pfd[1]);
	(*cmd)->redirs.pfd[1] = -1;
	return (_SUCCESS);
}

int	_exec_redirections(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_name && _swap_fd_redir_out(cmd))
		return (_FAILURE);
	if ((*cmd)->redirs.in_name && _swap_fd_redir_in(cmd))
		return (_FAILURE);
	if ((*cmd)->prev && !(*cmd)->redirs.in_name && _read_from_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->next && !(*cmd)->redirs.out_name && _write_to_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->prev && (*cmd)->redirs.in_name)
	{
		if ((*cmd)->prev->redirs.pfd[0] > 0)
			close((*cmd)->prev->redirs.pfd[0]);
		if ((*cmd)->prev->redirs.pfd[1] > 0)
			close((*cmd)->prev->redirs.pfd[1]);
	}
	if ((*cmd)->next && (*cmd)->redirs.out_name)
	{
		if ((*cmd)->redirs.pfd[0] > 0)
			close((*cmd)->redirs.pfd[0]);
		if ((*cmd)->redirs.pfd[1] > 0)
			close((*cmd)->redirs.pfd[1]);
	}
	return (_SUCCESS);
}
