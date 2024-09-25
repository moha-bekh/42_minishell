/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:03:41 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/25 17:04:19 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_sigint_handler(int sig)
{
	(void)sig;
	*_ptr_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	_set_signals(t_pdata data)
{
	sigemptyset(&data->shell.s_sigint.sa_mask);
	data->shell.s_sigint.sa_flags = 0;
	data->shell.s_sigint.sa_handler = _sigint_handler;
	sigaction(SIGINT, &data->shell.s_sigint, NULL);
	sigemptyset(&data->shell.s_sigquit.sa_mask);
	data->shell.s_sigquit.sa_flags = 0;
	data->shell.s_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
	return (_SUCCESS);
}


// int		*_ptr_errno;

// void	child_hndl(int sig)
// {
// 	if (sig == SIGTERM)
// 	{
// 		printf("%d\n", sig);
// 		exit(0);
// 	}
// 	else if (sig == SIGINT)
// 	{
// 		printf("%d\n", sig);
// 		exit(0);
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		printf("%d\n", sig);
// 		exit(0);
// 	}
// }

// void	_func_hndl(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		*_ptr_errno = 130;
// 		printf("\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("", 0);
// 		// rl_redisplay();
// 	}
// 	if (sig == SIGTERM)
// 	{
// 		ft_dprintf(1, "exit\n");
// 		exit(0);
// 	}
// }

// int	_set_signals(t_pdata data)
// {
// 	_ptr_errno = &data->_errno;
// 	data->shell.s_sig.sa_handler = _func_hndl;
// 	sigemptyset(&data->shell.s_sig.sa_mask);
// 	data->shell.s_sig.sa_flags = 0;

// 	// sigaction(SIGTERM, &data->s_sig, NULL);
// 	sigaction(SIGINT, &data->shell.s_sig, NULL);
// 	// sigaction(SIGQUIT, &data->s_sig, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	return (_SUCCESS);
// }
