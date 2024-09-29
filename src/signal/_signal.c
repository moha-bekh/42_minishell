/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:14:13 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/28 19:24:37 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void _hndl_hd_sigint(int sig)
{
	(void)sig;
	*g_ptr_errno = 130;
	exit(130);
}

// int	_set_sigint(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = _hndl_sigint;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int _hd_sigint(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = _hndl_hd_sigint;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_ign_sigint(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_dfl_sigint(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = SIG_DFL;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_ign_sigquit(t_pdata data)
// {
// 	data->shell.s_sigquit.sa_handler = SIG_IGN;
// 	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_dfl_sigquit(t_pdata data)
// {
// 	data->shell.s_sigquit.sa_handler = SIG_DFL;
// 	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }



// int	_sig_default(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = SIG_DFL;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	data->shell.s_sigquit.sa_handler = SIG_DFL;
// 	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_sig_ignore(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	data->shell.s_sigquit.sa_handler = SIG_IGN;
// 	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// int	_sig_proc(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = _sigint_handler;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	data->shell.s_sigquit.sa_handler = SIG_IGN;
// 	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }

// void	_hd_handler(int sig)
// {
// 	(void)sig;
// 	*g_ptr_errno = 130;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// int	_sig_here_doc(t_pdata data)
// {
// 	data->shell.s_sigint.sa_handler = _hd_handler;
// 	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }