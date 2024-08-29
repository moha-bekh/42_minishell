/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:16 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 04:55:30 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env_filled(t_pdata data, t_ppadlst dlst)
{
	int		i;
	int		sep;
	char	**env;

	if (!dlst || !*data->args.env)
		return ;
	env = data->args.env;
	i = -1;
	while (env[++i])
	{
		sep = _sep(env[i]);
		if (sep == 1 && env[i][0] == '_')
			continue ;
		_dlst_push_back(dlst, ft_substr(env[i], 0, sep), ft_strdup(env[i] + (sep
					+ 1)), 0);
	}
}

void	_data_init_env_n_export(t_pdata data)
{
	char	*buf;

	buf = NULL;
	if (!*data->args.env)
	{
		_dlst_push_back(&data->env, ft_strdup("OLDPWD"), NULL, 0);
		_dlst_push_back(&data->env, ft_strdup("PWD"), getcwd(buf, 4096), 0);
		_dlst_push_back(&data->export, ft_strdup("OLDPWD"), NULL, 0);
		_dlst_push_back(&data->export, ft_strdup("PWD"), getcwd(buf, 4096), 0);
		_dlst_sort(&data->export, false);
		return ;
	}
	_env_filled(data, &data->env);
	_env_filled(data, &data->export);
	_dlst_push_back(&data->env, ft_strdup("OLDPWD"), NULL, 0);
	_dlst_push_back(&data->export, ft_strdup("OLDPWD"), NULL, 0);
	_dlst_sort(&data->export, false);
}
