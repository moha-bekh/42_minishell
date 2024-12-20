/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:44:34 by moha              #+#    #+#             */
/*   Updated: 2024/10/25 11:52:50 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	_builtins_init(t_pdata data)
{
	t_pnlst	tmp;

	_dlst_push_back(&data->builtins, ft_strdup("cd"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("echo"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("env"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("exit"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("export"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("pwd"), NULL, 0);
	_dlst_push_back(&data->builtins, ft_strdup("unset"), NULL, 0);
	tmp = data->builtins->d_top;
	while (tmp)
	{
		if (!tmp->addr_1)
			return (_FAILURE);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_path_init(t_pdata data)
{
	data->args.env_path = ft_split(getenv("PATH"), ':');
	if (!data->args.env_path)
	{
		data->args.hard_paths = ft_split(_PATH, ':');
		if (!data->args.hard_paths)
			return (_FAILURE);
		data->args._hard_path = ft_strdup(_PATH);
		if (!data->args._hard_path)
			return (_FAILURE);
	}
	if (_path_slasher(data))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_data_init(t_pdata data, int ac, char **av, char **ev)
{
	*data = (t_data){0};
	data->args.ac = ac;
	data->args.av = av;
	data->args.env = ev;
	if (_path_init(data))
		return (_FAILURE);
	if (_builtins_init(data))
		return (_FAILURE);
	if (_env_init(data))
		return (_FAILURE);
	return (_SUCCESS);
}
