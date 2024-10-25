/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _sig_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:14:13 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/25 11:52:06 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_hndl_sigint(int sig)
{
	g_sig = sig;
	_get_data()->_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	_hndl_sigterm(int sig)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &_get_data()->shell.new_term) == -1)
		return (perror("tcsetattr"));
	_exit(sig);
}

int	_sig_init(t_pdata data)
{
	{
		sigemptyset(&data->shell.s_sigint.sa_mask);
		data->shell.s_sigint.sa_flags = 0;
		data->shell.s_sigint.sa_handler = _hndl_sigint;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);
	}
	{
		sigemptyset(&data->shell.s_sigterm.sa_mask);
		data->shell.s_sigterm.sa_flags = 0;
		data->shell.s_sigterm.sa_handler = _hndl_sigterm;
		sigaction(SIGTERM, &data->shell.s_sigterm, NULL);
	}
	{
		sigemptyset(&data->shell.s_sigquit.sa_mask);
		data->shell.s_sigquit.sa_flags = 0;
		data->shell.s_sigquit.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
	}
	return (_SUCCESS);
}
