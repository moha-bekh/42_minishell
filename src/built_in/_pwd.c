/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:02:08 by moha              #+#    #+#             */
/*   Updated: 2024/07/31 12:07:54 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pwd(t_pdata data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	data->_errno = 0;
	free(pwd);
}
