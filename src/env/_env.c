/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:16 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:42:51 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env_empty(t_pdata data, t_ppadlst dlst)
{
	char	*buf;

	buf = NULL;
	_dlst_push_back(dlst, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	data->args.old_pwd = (char *)(*dlst)->d_bot->addr_2;
	_dlst_push_back(dlst, ft_strdup("PWD"), getcwd(buf, 4096), 0);
	data->args.pwd = (char *)(*dlst)->d_bot->addr_2;
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

void	_add_oldpwd(t_pdata data, t_ppadlst dlst)
{
	t_pnlst	tmp;

	if (!dlst)
		return ;
	tmp = (*dlst)->d_top;
	while (tmp)
	{
		if (!ft_strcmp((char *)tmp->addr_1, "OLDPWD"))
		{
			data->args.old_pwd = (char *)tmp->addr_2;
			return ;
		}
		tmp = tmp->next;
	}
	_dlst_push_back(dlst, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	data->args.old_pwd = (char *)(*dlst)->d_bot->addr_2;
}

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
		_dlst_push_back(dlst, ft_substr(env[i], 0, sep), ft_strdup(env[i]
				+ (sep + 1)), 0);
		if (!ft_strcmp((char *)(*dlst)->d_bot->addr_1, "PWD"))
			data->args.pwd = (char *)(*dlst)->d_bot->addr_2;
		if (1 == ft_strcmp((char *)(*dlst)->d_bot->addr_1, "OLDPWD"))
			data->args.old_pwd = (char *)(*dlst)->d_bot->addr_2;
	}
}

void	_data_init_env_n_export(t_pdata data)
{
	if (!*data->args.env)
	{
		_env_empty(data, &data->env);
		_env_empty(data, &data->export);
		_dlst_sort(&data->export, false);
		return ;
	}
	_env_filled(data, &data->env);
	_env_filled(data, &data->export);
	_add_oldpwd(data, &data->env);
	_add_oldpwd(data, &data->export);
	_dlst_sort(&data->export, false);
}
