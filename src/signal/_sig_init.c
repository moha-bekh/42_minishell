/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _sig_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:14:13 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 19:32:49 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_hndl_sigint(int sig)
{
	if (sig == SIGINT)
	{
		_get_data()->_errno = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
		sigemptyset(&data->shell.s_sigquit.sa_mask);
		data->shell.s_sigquit.sa_flags = 0;
		data->shell.s_sigquit.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
	}
	return (_SUCCESS);
}
