/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:54 by moha              #+#    #+#             */
/*   Updated: 2024/08/12 16:35:52 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_echo(t_pdata data, char **arg)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (!arg[1])
		return (printf("\n"), _SUCCESS);
	if (arg[1][0] == '-' && arg[1][1] == 'n' && !arg[1][2])
	{
		new_line = false;
		i++;
	}
	while (arg[++i])
	{
		if (!strcmp(arg[i], "$?"))
			printf("%d", data->_errno);
		else
			printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (_SUCCESS);
}
