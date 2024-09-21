/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:03:41 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/21 19:01:34 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
