/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:53:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/29 19:47:50 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_set_redir_in(t_ppncmd cmd)
// {
// 	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
// 	if ((*cmd)->redirs.fd[0] < 0)
// 	{
// 		if (!(*cmd)->next)
// 			return (_err_print(_ERR_NO_FILE, (*cmd)->redirs.in_name, true,
// 1));
// 		_err_print(_ERR_NO_FILE, (*cmd)->redirs.in_name, true, 1);
// 		(*cmd)->redirs.fd[0] = open("/dev/null", O_RDONLY);
// 		if ((*cmd)->redirs.fd[0] < 0)
// 			return (_err_print(_ERR_NO_FILE, "/dev/null", true, 1));
// 		return (_SUCCESS);
// 	}
// 	if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
// 		return (_err_print("bash: dup2 failed", NULL, false, 1));
// 	if (close((*cmd)->redirs.fd[0]) < 0)
// 		return (_err_print("bash: close failed", NULL, false, 1));
// 	return (_SUCCESS);
// }

// int	_set_redir_out(t_ppncmd cmd)
// {
// 	if ((*cmd)->redirs.out_trunc)
// 		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCT);
// 	else
// 		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCA);
// 	if ((*cmd)->redirs.fd[1] < 0)
// 		return (_err_print(_ERR_IS_DIR, (*cmd)->redirs.out_name, true, 1));
// 	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
// 		return (_err_print("bash: dup2 failed", NULL, false, 1));
// 	if (close((*cmd)->redirs.fd[1]) < 0)
// 		return (_err_print("bash: close failed", NULL, false, 1));
// 	return (_SUCCESS);
// }

// int	_read_from_pipe(t_ppncmd cmd)
// {
// 	if (close((*cmd)->prev->redirs.pfd[1]) < 0)
// 		return (_err_print("bash: close failed", NULL, false, 1));
// 	if (dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO) < 0)
// 		return (_err_print("bash: dup2 failed", NULL, false, 1));
// 	if (close((*cmd)->prev->redirs.pfd[0]) < 0)
// 		return (_err_print("bash: close failed", NULL, false, 1));
// 	return (_SUCCESS);
// }

// int	_write_to_pipe(t_ppncmd cmd)
// {
// 	if (close((*cmd)->redirs.pfd[0]) < 0)
// 		return (_err_print("bash: close failed", NULL, false, 1));
// 	if (dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO) < 0)
// 		return (_err_print("bash: dup2 failed", NULL, false, 1));
// 	if (close((*cmd)->redirs.pfd[1]) < 0)
// 		return (_err_print("bash: close failed", NULL, false, 1));
// 	return (_SUCCESS);
// }

// int	_exec_redirections(t_ppncmd cmd)
// {
// 	if ((*cmd)->prev && _read_from_pipe(cmd))
// 		return (_FAILURE);
// 	if ((*cmd)->next && _write_to_pipe(cmd))
// 		return (_FAILURE);
// 	if ((*cmd)->redirs.in_name && _set_redir_in(cmd) && !(*cmd)->next)
// 		return (_FAILURE);
// 	if ((*cmd)->redirs.out_name && _set_redir_out(cmd))
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_exec_child_proc(t_pdata data, t_ppncmd cmd)
// {
// 	if (!*cmd)
// 		return (_FAILURE);
// 	data->s_sig.sa_handler = child_hndl;
// 	if (_exec_redirections(cmd))
// 		return (_FAILURE);
// 	if (execve((*cmd)->path, (*cmd)->args, data->args.env) < 0)
// 	{
// 		if (*cmd && (*cmd)->args && (*cmd)->args[0])
// 			_err_print(_ERR_NOT_FOUND, (*cmd)->args[0], true, 126);
// 		_data_clear(data);
// 		exit(126);
// 	}
// 	return (_FAILURE);
// }

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

int	_save_stdfds(t_pdata data)
{
	data->args._stdin = dup(STDIN_FILENO);
	data->args._stdout = dup(STDOUT_FILENO);
	return (_SUCCESS);
}

int	_restore_stdfds(t_pdata data)
{
	dup2(data->args._stdin, STDIN_FILENO);
	dup2(data->args._stdout, STDOUT_FILENO);
	return (_SUCCESS);
}

int	_swap_here_doc(t_ppncmd cmd)
{
	(*cmd)->redirs.here_fd = open((*cmd)->redirs.here_name, O_RDONLY);
	dup2((*cmd)->redirs.here_fd, STDIN_FILENO);
	close((*cmd)->redirs.here_fd);
	return (_SUCCESS);
}

int	_swap_redir_in(t_ppncmd cmd)
{
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	dup2((*cmd)->redirs.fd[0], STDIN_FILENO);
	close((*cmd)->redirs.fd[0]);
	return (_SUCCESS);
}

int	_swap_redir_out(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCT);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCA);
	dup2((*cmd)->redirs.fd[1], STDOUT_FILENO);
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}


int	_exec_redirections(t_pdata data, t_ppncmd cmd)
{
	(void)data;
	if ((*cmd)->redirs.in_name)
	{
		_swap_redir_in(cmd);
	}
	if ((*cmd)->redirs.out_name)
	{
		_swap_redir_out(cmd);
	}
	if ((*cmd)->next && !(*cmd)->redirs.out_name)
	{
		_write_to_pipe(cmd);
	}
	if ((*cmd)->prev && !(*cmd)->redirs.in_name)
	{
		_read_from_pipe(cmd);
	}
	return (_SUCCESS);
}

int	_exec_child_proc(t_pdata data, t_ppncmd cmd)
{
	data->s_sig.sa_handler = child_hndl;
	_exec_redirections(data, cmd);
	execve((*cmd)->path, (*cmd)->args, data->args.env);
	if ((*cmd)->args)
		_err_print(_ERR_NOT_FOUND, (*cmd)->args[0], true, 126);
	_data_clear(data);
	exit(126);
	return (_FAILURE);
}
