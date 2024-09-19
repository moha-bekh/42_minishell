/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:02:08 by moha              #+#    #+#             */
/*   Updated: 2024/08/22 18:22:39 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pwd(t_pdata data)
{
	char	*pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (_err_print(_ERR_PWD, NULL, true, 1));
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
	return (_SUCCESS);
}
