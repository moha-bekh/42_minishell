/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:55:16 by moha              #+#    #+#             */
/*   Updated: 2024/09/01 00:28:01 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pdata	_get_data(void)
{
	static t_data	data = {0};

	return (&data);
}

int	_err_print(char *str, void *arg, bool ptr, int _errno)
{
	t_pdata	data;

	data = _get_data();
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

char	*_env_get_value(t_pdata data, char *key)
{
	t_pnlst	tmp;

	tmp = data->env->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
			return ((char *)tmp->addr_2);
		tmp = tmp->next;
	}
	return (NULL);
}

int	_varstr_conv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
