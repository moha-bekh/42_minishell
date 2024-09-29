/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:53:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/28 18:52:36 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_exec_parent_proc(t_pdata data, t_ppncmd cmd)
// {
// 	data->shell.s_sigint.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &data->shell.s_sigint, NULL);
// 	if ((*cmd)->prev)
// 	{
// 		close((*cmd)->prev->redirs.pfd[1]);
// 		close((*cmd)->prev->redirs.pfd[0]);
// 	}
// 	return (_SUCCESS);
// }

// int	_exec_child_proc(t_pdata data, t_ppncmd cmd)
// {
// 	char	**env;

// 	env = _ltoa(data->env);
// 	execve((*cmd)->path, (*cmd)->args, env);
// 	if ((*cmd)->args)
// 		_err_print(_ERR_NOT_FOUND, (*cmd)->args[0], true, 127);
// 	ft_free_arr(env);
// 	_data_clear(data);
// 	exit(127);
// 	return (_FAILURE);
// }

// int	_exec_proc(t_pdata data, t_ppncmd cmd)
// {
// 	if ((*cmd)->next)
// 	{
// 		if (pipe((*cmd)->redirs.pfd) < 0)
// 			return (_err_print("bash: pipe failed", NULL, false, 1));
// 	}
// 	(*cmd)->pid = fork();
// 	if ((*cmd)->pid < 0)
// 		return (_err_print("bash: fork failed", NULL, false, 1));
// 	if (!(*cmd)->pid)
// 	{
				
// 		data->shell.s_sigint.sa_handler = SIG_DFL;
// 		data->shell.s_sigquit.sa_handler = SIG_DFL;
// 		sigaction(SIGINT, &data->shell.s_sigint, NULL);
// 		sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);

// 		_exec_redirections(cmd);

// 		if (_is_builtin(data, (*cmd)->args))
// 		{
// 			data->_errno = _exec_builtin(data, cmd);
// 			_data_clear(data);
// 			exit(data->_errno);
// 		}
// 		else
// 		{
// 			if (_resolve_path(data, cmd))
// 				return (_FAILURE);
// 			if (_exec_child_proc(data, cmd))
// 				return (_FAILURE);
// 		}
// 	}
// 	else
// 		_exec_parent_proc(data, cmd);
// 	return (_SUCCESS);
// }
