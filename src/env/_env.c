/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:16 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 00:45:11 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env_empty(t_pdata data, u_padllst *dllst)
{
	char	*buf;

	buf = NULL;
	_dllst_push_back(dllst, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	data->args.old_pwd = (char *)(*dllst)->d_bot->addr_2;
	_dllst_push_back(dllst, ft_strdup("PWD"), getcwd(buf, 4096), 0);
	data->args.pwd = (char *)(*dllst)->d_bot->addr_2;
}

int	_sep(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (i);
}

void	_add_oldpwd(t_pdata data, u_padllst *dllst)
{
	t_pnlst	tmp;

	if (!dllst)
		return ;
	tmp = (*dllst)->d_top;
	while (tmp)
	{
		if (!ft_strcmp((char *)tmp->addr_1, "OLDPWD"))
		{
			data->args.old_pwd = (char *)tmp->addr_2;
			return ;
		}
		tmp = tmp->next;
	}
	_dllst_push_back(dllst, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	data->args.old_pwd = (char *)(*dllst)->d_bot->addr_2;
}

void	_env_filled(t_pdata data, u_padllst *dllst)
{
	int		i;
	int		sep;
	char	**env;

	if (!dllst || !*data->args.env)
		return ;
	env = data->args.env;
	i = -1;
	while (env[++i])
	{
		sep = _sep(env[i]);
		if (sep == 1 && env[i][0] == '_')
			continue ;
		_dllst_push_back(dllst, ft_substr(env[i], 0, sep), ft_strdup(env[i]
				+ (sep + 1)), 0);
		if (!ft_strcmp((char *)(*dllst)->d_bot->addr_1, "PWD"))
			data->args.pwd = (char *)(*dllst)->d_bot->addr_2;
		if (1 == ft_strcmp((char *)(*dllst)->d_bot->addr_1, "OLDPWD"))
			data->args.old_pwd = (char *)(*dllst)->d_bot->addr_2;
	}
}

void	_data_init_env_n_export(t_pdata data)
{
	if (!*data->args.env)
	{
		_env_empty(data, &data->env);
		_env_empty(data, &data->export);
		_dllst_sort(&data->export, false);
		return ;
	}
	_env_filled(data, &data->env);
	_env_filled(data, &data->export);
	_add_oldpwd(data, &data->env);
	_add_oldpwd(data, &data->export);
	_dllst_sort(&data->export, false);
}
