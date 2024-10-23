/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alblanc <alblanc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:58:08 by alblanc           #+#    #+#             */
/*   Updated: 2024/10/23 16:03:23 by alblanc          ###   ########.fr       */
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
