/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:50 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 05:06:07 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_cd_home(t_pdata data)
{
	t_pnlst	tmp;

	if (!data->env)
		return (_err_print("bash: cd: HOME not set\n", NULL, false, 1));
	tmp = data->env->d_top;
	while (tmp)
	{
		if (!ft_strncmp(tmp->addr_1, "HOME", 4))
		{
			if (!chdir(tmp->addr_2))
				return (_err_print("chdir", NULL, true, 1));
		}
		tmp = tmp->next;
	}
	return (_err_print("bash: cd: HOME not set\n", NULL, false, 1));
}

int	_cd(t_pdata data, char **args)
{
	char	oldpwd[4096];
	char	pwd[4096];
	char	*tmp;

	if (getcwd(oldpwd, 4096) == NULL)
		return (_err_print("getcwd", NULL, true, 1));
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	_export(data, &tmp);
	free(tmp);
	if (!args[1] && _cd_home(data))
		return (_FAILURE);
	else if (args[1] && !chdir(args[1]))
		return (_err_print("chdir", NULL, true, 1));
	if (getcwd(pwd, 4096) == NULL)
		return (_err_print("getcwd", NULL, true, 1));
	tmp = ft_strjoin("PWD=", pwd);
	_export(data, &tmp);
	free(tmp);
	return (_SUCCESS);
}
