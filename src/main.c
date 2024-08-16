/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/08/16 07:53:51 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*_ptr_errno;

int	_skip(t_pdata data, char *input)
{
	(void)data;
	if (!*input)
		return (_IS);
	if (!ft_strncmp(input, "\n", 1))
		return (_IS);
	if (!ft_strncmp(input, "clear", 5))
	{
		system("clear");
		return (_IS);
	}
	return (_NOT);
}

void	sa_hndl(int sig)
{
	if (sig == SIGTERM)
	{
		printf("exit\n");
		exit(0);
	}
	else if (sig == SIGINT)
	{
		*_ptr_errno = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else if (sig == SIGQUIT)
		return ;
}

void	child_hndl(int sig)
{
	if (sig == SIGTERM)
	{
		printf("%d\n", sig);
		exit(0);
	}
	else if (sig == SIGINT)
	{
		printf("%d\n", sig);
		exit(0);
	}
}

int	_set_signals(t_pdata data)
{
	data->sa.sa_handler = sa_hndl;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = 0;
	if (sigaction(SIGINT, &data->sa, NULL) == -1)
		return (perror("sigaction"), _FAILURE);
	if (sigaction(SIGQUIT, &data->sa, NULL) == -1)
		return (perror("sigaction"), _FAILURE);
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	t_data	data;

	if (_data_init(&data, ac, av, ev))
		return (_data_cleaner(&data), _FAILURE);
	_ptr_errno = &data._errno;
	while (1)
	{
		data.input = readline(">$ ");
		if (!data.input)
		{
			_data_cleaner(&data);
			sa_hndl(SIGTERM);
			return (_FAILURE);
		}
		add_history(data.input);
		if (_skip(&data, data.input))
		{
			_data_clear_lists(&data);
			continue ;
		}
		if (_token(&data))
			return (_data_cleaner(&data), _FAILURE);
		if (_tok_check(&data))
		{
			_data_clear_lists(&data);
			continue ;
		}
		// _tok_print(data.tok);
		_expand(&data);
		_join_strings(&data);
		data.tree = _tree(&data);
		if (_parsing(&data, data.tree))
		{
			_data_clear_lists(&data);
			continue ;
		}
		// _tok_print(data.tok);
		// _op_bt_print(data.tree, true, 0);
		_exec(&data, data.tree);
		_data_clear_lists(&data);
	}
	return (_data_cleaner(&data), _SUCCESS);
}
