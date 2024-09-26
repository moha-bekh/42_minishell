/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:14:13 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 19:15:06 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_sigint_handler(int sig)
{
	(void)sig;
	*g_ptr_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	_set_child_signals(t_pdata data)
{
	data->shell.s_sigint.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
		return (_FAILURE);
	data->shell.s_sigquit.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
		return (_FAILURE);
	return (_SUCCESS);
}

int _set_parent_ignore_signals(t_pdata data)
{
    data->shell.s_sigint.sa_handler = SIG_IGN;
    if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
        return (_FAILURE);
    data->shell.s_sigquit.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
        return (_FAILURE);
    return (_SUCCESS);
}

int	_set_parent_signals(t_pdata data)
{
	data->shell.s_sigint.sa_handler = _sigint_handler;
	if (sigaction(SIGINT, &data->shell.s_sigint, NULL) == -1)
		return (_FAILURE);
	data->shell.s_sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &data->shell.s_sigquit, NULL) == -1)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_signals_init(t_pdata data)
{
	sigemptyset(&data->shell.s_sigint.sa_mask);
	data->shell.s_sigint.sa_flags = 0;
	sigemptyset(&data->shell.s_sigquit.sa_mask);
	data->shell.s_sigquit.sa_flags = 0;
	if (_set_parent_signals(data))
		return (_FAILURE);
	return (_SUCCESS);
}
