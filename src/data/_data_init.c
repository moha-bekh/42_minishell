/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:44:34 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 05:19:49 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	_data_init(t_pdata data, int ac, char **av, char **ev)
{
	data->args.ac = ac;
	data->args.av = av;
	data->args.env = ev;
	data->args.env_path = ft_split(getenv("PATH"), ':');
	if (!data->args.env_path)
	{
		data->args.hard_path = ft_split(_PATH, ':');
		if (!data->args.hard_path)
			return (_FAILURE);
	}
	// data->args._stdin = dup(STDIN_FILENO);
	// data->args._stdout = dup(STDOUT_FILENO);
	_path_slash(data);
	_data_init_builtins(data);
	_data_init_env_n_export(data);
	return (_SUCCESS);
}
