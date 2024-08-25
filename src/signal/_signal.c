/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:03:41 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/23 18:35:25 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				*_ptr_errno;

void	child_hndl(int sig)
{
	if (sig == SIGTERM)
	{
		printf("%d\n", sig);
		exit(0);
	}
	else if (sig == SIGINT)
	{
		printf("%d\n", sig);
		exit(0);
	}
}

void	sig_hndl(int sig)
{
	if (sig == SIGTERM)
	{
		printf("exit\n");
		exit(0);
	}
	else if (sig == SIGINT)
	{
		*_ptr_errno = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else if (sig == SIGQUIT)
		return ;
}

int	_set_signals(t_pdata data)
{
	(void)data;
	// _ptr_errno = &data->_errno;
	// data->s_sig.sa_handler = sig_hndl;
	// sigemptyset(&data->s_sig.sa_mask);
	// data->s_sig.sa_flags = 0;
	// if (sigaction(SIGINT, &data->s_sig, NULL) == -1)
	// 	return (perror("sigaction: SIGINT"), _FAILURE);
	// if (sigaction(SIGQUIT, &data->s_sig, NULL) == -1)
	// 	return (perror("sigaction: SIGQUIT"), _FAILURE);
	return (_SUCCESS);
}
