/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:10:09 by moha              #+#    #+#             */
/*   Updated: 2024/09/20 02:42:19 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_needed(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (true);
	}
	return (true);
}
int	_xpd_conv(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (true);
	return (false);
}

// int	_xpd_errno(t_pdata data)
// {
// 	char	*value;

// 	value = ft_itoa(data->_errno);
// 	_dlst_push_back(&data->xpd, value, NULL, 0);
// 	return (_SUCCESS);
// }

// int	_xpd_var_env(t_pdata data, char *tmp)
// {
// 	char	*value;

// 	value = _env_get_value(data, tmp);
// 	if (value)
// 		_dlst_push_back(&data->xpd, ft_strdup(value), NULL, 0);
// 	return (_SUCCESS);
// }
