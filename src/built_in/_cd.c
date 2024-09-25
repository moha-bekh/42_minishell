/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:50 by moha              #+#    #+#             */
/*   Updated: 2024/09/25 22:58:26 by mbekheir         ###   ########.fr       */
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
				return (_err_print("chdir\n", NULL, true, 1));
			return (_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (_err_print("bash: cd: HOME not set\n", NULL, false, 1));
}

int	_set_old_pwd(t_pdata data)
{
	char	**oldpwd;
	char	*tmp;

	oldpwd = malloc(sizeof(char *) * 3);
	if (!oldpwd)
		return (_FAILURE);
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		tmp = ft_strdup(_env_get_value(data, "PWD"));
		if (!tmp)
			return (_FAILURE);
		_err_print(_ERR_PWD, NULL, true, 1);
	}
	oldpwd[1] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	oldpwd[2] = NULL;
	_export(data, oldpwd);
	free(oldpwd[1]);
	free(oldpwd);
	return (_SUCCESS);
}

int	_set_new_pwd(t_pdata data)
{
	char	**pwd;
	char	*tmp;

	pwd = malloc(sizeof(char *) * 3);
	if (!pwd)
		return (_FAILURE);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (_FAILURE);
	pwd[1] = ft_strjoin("PWD=", tmp);
	free(tmp);
	pwd[2] = NULL;
	_export(data, pwd);
	free(pwd[1]);
	free(pwd);
	return (_SUCCESS);
}

int	_cd(t_pdata data, char **args)
{
	if (_set_old_pwd(data))
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
	if (_set_new_pwd(data))
		return (_FAILURE);
	return (_SUCCESS);
}
