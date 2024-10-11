/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:38:51 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 18:02:31 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_env_filled(t_pdata data, t_ppadlst dlst)
{
	char	**env;
	char	*value;
	char	*key;
	int		i;

	if (!dlst)
		return (_FAILURE);
	env = data->args.env;
	i = -1;
	while (env[++i])
	{
		if (env[i][0] == '_')
			continue ;
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (!key)
			return (_FAILURE);
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!value)
		{
			free(key);
			return (_FAILURE);
		}
		_dlst_push_back(dlst, key, value, 0);
	}
	return (_SUCCESS);
}

int	_set_oldpwd(t_pdata data)
{
	t_pnlst	tmp;

	tmp = data->export->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, "OLDPWD"))
			return (_SUCCESS);
		tmp = tmp->next;
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
	_dlst_push_back(&data->env, ft_strdup("PWD"), getcwd(buf, 4096), 0);
	if (!data->env->d_bot->addr_1 || !data->env->d_bot->addr_2)
		return (_FAILURE);
	_dlst_push_back(&data->export, ft_strdup("PWD"), getcwd(buf, 4096), 0);
	if (!data->export->d_bot->addr_1 || !data->export->d_bot->addr_2)
		return (_FAILURE);
	// _dlst_push_back(&data->env, ft_strdup("SHLVL"), ft_strdup("1"), 0);
	// if (!data->env->d_bot->addr_1)
	// 	return (_FAILURE);
	// _dlst_push_back(&data->export, ft_strdup("SHLVL"), ft_strdup("1"), 0);
	// if (!data->export->d_bot->addr_1)
	// 	return (_FAILURE);
	_dlst_push_back(&data->env, ft_strdup("OLDPWD"), NULL, 0);
	if (!data->env->d_bot->addr_1)
		return (_FAILURE);
	_dlst_push_back(&data->export, ft_strdup("OLDPWD"), NULL, 0);
	if (!data->export->d_bot->addr_1)
		return (_FAILURE);
	return (_SUCCESS);
}

// int	_inc_shlvl(t_pdata data, t_ppadlst env)
// {
// 	t_pnlst	tmp;
// 	int		shlvl;

// 	if (!*data->args.env)
// 		return (_SUCCESS);
// 	tmp = (*env)->d_top;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->addr_1, "SHLVL"))
// 		{
// 			shlvl = ft_atoi(tmp->addr_2);
// 			printf("shlvl: %d\n", shlvl);
// 			shlvl++;
// 			printf("shlvl: %d\n", shlvl);
// 			free(tmp->addr_2);
// 			tmp->addr_2 = ft_itoa(shlvl);
// 			if (!tmp->addr_2)
// 				return (_FAILURE);
// 			return (_SUCCESS);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (_FAILURE);
// }

int	_env_init(t_pdata data)
{
	if (!*data->args.env && _env_empty(data))
		return (_FAILURE);
	else
	{
		if (_data_env_filled(data, &data->env) || _data_env_filled(data,
				&data->export))
			return (_FAILURE);
		if (_set_oldpwd(data))
			return (_FAILURE);
	}
	return (_dlst_sort(&data->export, false), _SUCCESS);
}
