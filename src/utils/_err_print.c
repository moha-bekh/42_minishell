/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:38:08 by oek               #+#    #+#             */
/*   Updated: 2024/10/11 03:42:46 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_err_print(char *str, void *arg, bool ptr, int _errno)
{
	if (!arg)
		ft_dprintf(2, str);
	else if (arg && ptr)
		ft_dprintf(2, str, (char *)arg);
	else
		ft_dprintf(2, str, *((char *)arg));
	if (_errno)
		*g_ptr_errno = _errno;
	return (_errno);
}
