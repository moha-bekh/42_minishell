/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:54 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:51:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_echo(t_pdata data, t_ppncmd cmd)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (!(*cmd)->args[1])
		return (printf("\n"), _SUCCESS);
	if ((*cmd)->args[1][0] == '-' && (*cmd)->args[1][1] == 'n'
		&& !(*cmd)->args[1][2])
	{
		new_line = false;
		i++;
	}
	while ((*cmd)->args && (*cmd)->args[++i])
	{
		if (!strcmp((*cmd)->args[i], "$?"))
			printf("%d", data->_errno);
		else
			printf("%s", (*cmd)->args[i]);
		if ((*cmd)->args[i + 1])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (_SUCCESS);
}
