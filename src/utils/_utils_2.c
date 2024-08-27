/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:55:16 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 13:38:23 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pdata	get_data(void)
{
	static t_data	data = {0};

	return (&data);
}

int	_alloc(void **target, size_t size)
{
	if (!size)
		return (_FAILURE);
	(*target) = malloc(size);
	if (!(*target))
		return (_ALLOC);
	ft_memset((*target), 0, size);
	return (_SUCCESS);
}

int	_err_print(char *str, void *arg, bool ptr, int _errno)
{
	t_pdata	data;

	data = get_data();
	if (!arg)
		ft_dprintf(2, str);
	else if (arg && ptr)
		ft_dprintf(2, str, (char *)arg);
	else
		ft_dprintf(2, str, *((char *)arg));
	if (_errno)
		data->_errno = _errno;
	return (_errno);
}
