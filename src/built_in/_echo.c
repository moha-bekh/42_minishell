/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:54 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 05:01:08 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_echo(t_pdata data, char **args)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (!args[1])
		return (printf("\n"), _SUCCESS);
	if (args[1][0] == '-' && args[1][1] == 'n' && !args[1][2])
	{
		new_line = false;
		i++;
	}
	while (args && args[++i])
	{
		if (!strcmp(args[i], "$?"))
			printf("%d", data->_errno);
		else
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (_SUCCESS);
}
