/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _sig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:14:46 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/23 01:50:44 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_hndl_hd_sigint(int sig)
{
	(void)sig;
	_get_data()->_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	_data_clear(_get_data());
}

void	_sig_child_sigint(int sig)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &_get_data()->shell.new_term) == -1)
		return (perror("tcsetattr"));
	_exit(sig);
}

int	_sig_child_dfl(t_pdata data)
{
	data->shell.s_sigint.sa_handler = _sig_child_sigint;
	if (sigaction(SIGINT, &data->shell.s_sigint, NULL))
		return (_FAILURE);
	data->shell.s_sigquit.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_sig_parent_ign(t_pdata data)
{
	data->shell.s_sigint.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &data->shell.s_sigint, NULL))
		return (_FAILURE);
	data->shell.s_sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_sig_parent_restore(t_pdata data)
{
	data->shell.s_sigint.sa_handler = _hndl_sigint;
	if (sigaction(SIGINT, &data->shell.s_sigint, NULL))
		return (_FAILURE);
	data->shell.s_sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL))
		return (_FAILURE);
	return (_SUCCESS);
}
