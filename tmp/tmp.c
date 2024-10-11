
int	_pars_pipe_lines(t_ppbtree node)
{
	t_pnlst	tmp;

	_cmd_push_back(&(*node)->cmd_line, (*node)->token);
	tmp = (*node)->token;
	while (tmp && (!(*node)->root || ((*node)->root
				&& tmp != (*node)->root->token)))
	{
		if (tmp->x == _PIPE)
			_cmd_push_back(&(*node)->cmd_line, tmp->next);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_pars_args_proc(t_ppncmd cmd)
{
	int	i;

	if (!*cmd)
		return (_FAILURE);
	(*cmd)->args = NULL;
	i = _nb_lnargs((*cmd)->token);
	if (i && (_alloc((void **)&(*cmd)->args, sizeof(char *) * (i + 1))
			|| !(*cmd)->args))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_pars_proc(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	int		i;
	char	*str;

	i = 0;
	str = (*token)->addr_1;
	if (_tok_id((*token)->x, _TYP_REDIRS))
	{
		if (_pars_redirs(data, cmd, token, inside))
		{
			data->_errno = 1;
			return (_FAILURE);
		}
	}
	else if (inside && str && str[0])
	{
		(*cmd)->args[i++] = ft_strdup(str);
		if (!(*cmd)->args[i - 1])
			return (_FAILURE);
	}
	else if (!inside && str && str[0])
	{
		data->_errno = 2;
		return (ft_dprintf(2, _ERR_TOKEN, str), _FAILURE);
	}
	return (_SUCCESS);
}

int	_pars_args_line(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	t_pnlst	tmp;

	if (!*cmd || (inside && _pars_args_proc(cmd)))
		return (_FAILURE);
	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (_pars_proc(data, cmd, &tmp, inside))
			return (_FAILURE);
		tmp = tmp->next;
	}
	if (tmp && tmp->x == ')' && tmp->next && _pars_args_line(data, cmd,
			&tmp->next, false))
		return (_FAILURE);
	return (_SUCCESS);
}
