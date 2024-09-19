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

	// pwd = getcwd(NULL, 0);
	pwd = _env_get_value(data, "PWD");
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
	return (_SUCCESS);
}
