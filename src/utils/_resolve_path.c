/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _resolve_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/04 16:43:55 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_get_path(t_pdata data, t_ppncmd cmd)
{
	char	**path;
	char	*prog;
	int		i;

	if (data->args.env_path)
		path = data->args.env_path;
	else if (*data->args.hard_path)
		path = data->args.hard_path;
	else
		return (_FAILURE);
	prog = (*cmd)->args[0];
	i = -1;
	while (path[++i])
	{
		(*cmd)->path = ft_strjoin(path[i], prog);
		if (!(*cmd)->path)
			continue ;
		if (!access((*cmd)->path, F_OK) && !access((*cmd)->path, X_OK))
			return (_SUCCESS);
		free((*cmd)->path);
		(*cmd)->path = NULL;
	}
	return (_FAILURE);
}

int	_is_path(t_ppncmd cmd)
{
	if (!access((*cmd)->args[0], X_OK))
	{
		(*cmd)->path = ft_strdup((*cmd)->args[0]);
		if (!(*cmd)->path)
			return (_FAILURE);
	}
	else
		exit(_err_print(_ERR_PERM, (*cmd)->args[0], true, 126));
	return (_SUCCESS);
}

int	_resolve_path(t_pdata data, t_ppncmd cmd)
{
	struct stat buf;
	char	*prog;

	if (!(*cmd)->args)
	{
		(*cmd)->path = ft_strdup("");
		if (!(*cmd)->path)
			return (_FAILURE);
	}
	else
	{
		prog = (*cmd)->args[0];
		if (ft_strchr(prog, '/') && access(prog, F_OK))
			exit (_err_print(_ERR_NO_FILE, prog, true, 127));
		if (ft_strchr(prog, '/') && !access(prog, F_OK))
		{
			if (lstat(prog, &buf) == -1)
				perror("lstat");
			if (S_ISDIR(buf.st_mode))
				exit (_err_print(_ERR_IS_DIR, prog, true, 126));
			if (_is_path(cmd))
				return (_FAILURE);
		}
		else if (_get_path(data, cmd))
		{
			(*cmd)->path = ft_strdup("");
			if (!(*cmd)->path)
				return (_FAILURE);
		}
	}
	return (_SUCCESS);
}
