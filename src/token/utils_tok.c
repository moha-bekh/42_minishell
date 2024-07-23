/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:18:25 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 22:19:21 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_is(char *str, char a)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == a)
			return (IT_IS);
	return (IS_NT);
}

int	_tok_syntax_err(char a, int n)
{
	int	i;

	i = -1;
	ft_putstr_fd(_SYNTAX_ERR, STDERR_FILENO);
	while (++i < n)
		ft_putchar_fd(a, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (RET_ERR);
}

int	_tok_syntax_close_err(char a)
{
	ft_putstr_fd(_SYNTAX_CLOSE_ERR, STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putstr_fd("' must be closed\n", STDERR_FILENO);
	return (RET_ERR);
}
