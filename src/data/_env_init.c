/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:38:51 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/25 22:44:16 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_env_filled(t_pdata data, t_ppadlst dlst)
{
	int		i;
	int		sep;
	char	**env;

	if (!dlst || !*data->args.env)
		return (_FAILURE);
	env = data->args.env;
	i = -1;
	while (env[++i])
	{
		sep = _sep(env[i]);
		if (sep == 1 && env[i][0] == '_')
			continue ;
		_dlst_push_back(dlst, ft_substr(env[i], 0, sep), ft_strdup(env[i] + (sep
					+ 1)), 0);
		if (!(*dlst)->d_bot->addr_1 || !(*dlst)->d_bot->addr_2)
			return (_FAILURE);
	}
	return (_SUCCESS);
}

int	_set_oldpwd(t_pdata data)
{
	char	**tmp;
	int		i;

	tmp = data->args.env;
	i = -1;
	while (tmp[++i])
	{
		if (!ft_strncmp(tmp[i], "OLDPWD", 6))
			return (_SUCCESS);
	}
	_dlst_push_back(&data->env, ft_strdup("OLDPWD"), NULL, 0);
	if (!data->env->d_bot->addr_1)
		return (_FAILURE);
	_dlst_push_back(&data->export, ft_strdup("OLDPWD"), NULL, 0);
	if (!data->export->d_bot->addr_1)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_env_empty(t_pdata data)
{
	char	*buf;

	buf = NULL;
	_dlst_push_back(&data->env, ft_strdup("OLDPWD"), NULL, 0);
	if (!data->env->d_bot->addr_1)
		return (_FAILURE);
	_dlst_push_back(&data->env, ft_strdup("PWD"), getcwd(buf, 4096), 0);
	if (!data->env->d_bot->addr_1 || !data->env->d_bot->addr_2)
		return (_FAILURE);
	_dlst_push_back(&data->export, ft_strdup("OLDPWD"), NULL, 0);
	if (!data->export->d_bot->addr_1)
		return (_FAILURE);
	_dlst_push_back(&data->export, ft_strdup("PWD"), getcwd(buf, 4096), 0);
	if (!data->export->d_bot->addr_1 || !data->export->d_bot->addr_2)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_env_init(t_pdata data)
{
	if (!*data->args.env && _env_empty(data))
		return (_FAILURE);
	else
	{
		if (_set_oldpwd(data))
			return (_FAILURE);
		if (_data_env_filled(data, &data->env) || _data_env_filled(data,
				&data->export))
			return (_FAILURE);
	}
	return (_dlst_sort(&data->export, false), _SUCCESS);
}
