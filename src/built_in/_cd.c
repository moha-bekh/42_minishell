/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:50 by moha              #+#    #+#             */
/*   Updated: 2024/09/18 18:46:16 by oek              ###   ########.fr       */
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
			if (chdir(tmp->addr_2) < 0)
				return (_err_print("chdir", NULL, true, 1));
			return (_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (_err_print("bash: cd: HOME not set\n", NULL, false, 1));
}

int _oldpwd(t_pdata data)
{
	char **oldpwd;
	char *tmp;

	oldpwd = malloc(sizeof(char *) * 3);
	if (!oldpwd)
		return (_FAILURE);
	tmp = getcwd(NULL, 0);
	oldpwd[1] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	oldpwd[2] = NULL;
	_export(data, oldpwd);
	free(oldpwd[1]);
	free(oldpwd);
	return (_SUCCESS);
}

int	_cd(t_pdata data, char **args)
{
	char **pwd;
	char *tmp;

	if (_oldpwd(data))
		return (_FAILURE);
	if (!args[1] && _cd_home(data))
		return (_FAILURE);
	if (args[1])
	{
		if (!ft_strcmp(args[1], "~"))
			_cd_home(data);
		else if (chdir(args[1]) < 0)
			return (_err_print(_ERR_NO_DIR, args[1], true, 1));
	}
	pwd = malloc(sizeof(char *) * 3);
	if (!pwd)
		return (_FAILURE);
	tmp = getcwd(NULL, 0);
	pwd[1] = ft_strjoin("PWD=", tmp);
	free(tmp);
	pwd[2] = NULL;
	_export(data, pwd);
	free(pwd[1]);
	free(pwd);
	return (_SUCCESS);
}
