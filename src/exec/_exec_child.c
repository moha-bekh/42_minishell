/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:53:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/29 05:47:27 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_redir_in(t_ppncmd cmd)
{
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	if ((*cmd)->redirs.fd[0] < 0)
	{
		if (!(*cmd)->next)
			return (_err_print(_ERR_NO_FILE, (*cmd)->redirs.in_name, true, 1));
		_err_print(_ERR_NO_FILE, (*cmd)->redirs.in_name, true, 1);
		(*cmd)->redirs.fd[0] = open("/dev/null", O_RDONLY);
		if ((*cmd)->redirs.fd[0] < 0)
			return (_err_print(_ERR_NO_FILE, "/dev/null", true, 1));
		return (_SUCCESS);
	}
	if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (close((*cmd)->redirs.fd[0]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	return (_SUCCESS);
}

int	_set_redir_out(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCT);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCA);
	if ((*cmd)->redirs.fd[1] < 0)
		return (_err_print(_ERR_IS_DIR, (*cmd)->redirs.out_name, true, 1));
	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (close((*cmd)->redirs.fd[1]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	return (_SUCCESS);
}

int	_read_from_pipe(t_ppncmd cmd)
{
	if (close((*cmd)->prev->redirs.pfd[1]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	if (dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (close((*cmd)->prev->redirs.pfd[0]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	return (_SUCCESS);
}

int	_write_to_pipe(t_ppncmd cmd)
{
	if (close((*cmd)->redirs.pfd[0]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	if (dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (close((*cmd)->redirs.pfd[1]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	return (_SUCCESS);
}

int	_exec_redirections(t_ppncmd cmd)
{
	if ((*cmd)->prev && _read_from_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->next && _write_to_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->redirs.in_name && _set_redir_in(cmd) && !(*cmd)->next)
		return (_FAILURE);
	if ((*cmd)->redirs.out_name && _set_redir_out(cmd))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_exec_child_proc(t_pdata data, t_ppncmd cmd)
{
	if (!*cmd)
		return (_FAILURE);
	data->s_sig.sa_handler = child_hndl;
	if (_exec_redirections(cmd))
		return (_FAILURE);
	if (execve((*cmd)->path, (*cmd)->args, data->args.env) < 0)
	{
		if (*cmd && (*cmd)->args && (*cmd)->args[0])
			_err_print(_ERR_NOT_FOUND, (*cmd)->args[0], true, 126);
		_data_clear(data);
		exit(126);
	}
	return (_FAILURE);
}
