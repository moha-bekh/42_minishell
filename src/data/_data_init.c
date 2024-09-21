/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:44:34 by moha              #+#    #+#             */
/*   Updated: 2024/09/21 19:23:38 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*_ptr_errno;

void	_data_init_builtins(t_pdata data)
{
	_dlst_push_back(&data->builtins, ft_strdup("cd"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("echo"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("env"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("exit"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("export"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("pwd"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("unset"), NULL, 0);
}

void	_data_env_filled(t_pdata data, t_ppadlst dlst)
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
		_dlst_push_back(dlst, ft_substr(env[i], 0, sep), ft_strdup(env[i] + (sep + 1)), 0);
	}
}

void _set_oldpwd(t_pdata data)
{
	char **tmp;
	int i;

	tmp = data->args.env;
	i = -1;
	while (tmp[++i])
	{
		if (!ft_strncmp(tmp[i], "OLDPWD", 6))
			return ;
	}
	_dlst_push_back(&data->env, ft_strdup("OLDPWD"), NULL, 0);
	_dlst_push_back(&data->export, ft_strdup("OLDPWD"), NULL, 0);
	return ;
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
	_set_oldpwd(data);
	_data_env_filled(data, &data->env);
	_data_env_filled(data, &data->export);
	_dlst_sort(&data->export, false);
}

int	_data_init(t_pdata data, int ac, char **av, char **ev)
{
	data->args.ac = ac;
	data->args.av = av;
	data->args.env = ev;
	_ptr_errno = &data->_errno;
	data->args.env_path = ft_split(getenv("PATH"), ':');
	if (!data->args.env_path)
	{
		data->args.hard_path = ft_split(_PATH, ':');
		if (!data->args.hard_path)
			return (_FAILURE);
	}
	_path_slasher(data);
	_data_init_builtins(data);
	_data_init_env_n_export(data);
	return (_SUCCESS);
}
