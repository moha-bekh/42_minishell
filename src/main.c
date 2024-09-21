/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/09/21 19:22:26 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void _sigint_handler(int sig)
{
	(void)sig;
	*_ptr_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void _set_signals(t_pdata data)
{
	sigemptyset(&data->shell.s_sigint.sa_mask);
	data->shell.s_sigint.sa_flags = 0;
	data->shell.s_sigint.sa_handler = _sigint_handler;
	sigaction(SIGINT, &data->shell.s_sigint, NULL);

	sigemptyset(&data->shell.s_sigquit.sa_mask);
	data->shell.s_sigquit.sa_flags = 0;
	data->shell.s_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
}

int	_set_shell(t_pdata data)
{
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &data->shell.org_term);
		data->shell.new_term = data->shell.org_term;
		data->shell.new_term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term);
	}
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	if (_data_init(&data, ac, av, ev))
		return (_data_clear(&data), _FAILURE);
	_set_signals(&data);
	while (true)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			return (printf("exit\n"), _data_clear(&data));
		add_history(data.prompt);
		if (_tok_list(&data) && !_data_structs_clear(&data))
			continue ;
		_tree_builder(&data.tree, data.tokens->d_top);
		if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
			continue ;
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}

// int main(int ac, char **av, char **ev)
// {
// 	// struct termios	org_term;
// 	// struct termios new_term;
// 	struct sigaction s_sigint;
// 	struct sigaction s_siquit;
// 	char *line;

// 	if (isatty(STDIN_FILENO))
// 	{
// 		sigemptyset(&s_sigint.sa_mask);
// 		s_sigint.sa_flags = 0;
// 		s_sigint.sa_handler = _sigint_handler;
// 		sigaction(SIGINT, &s_sigint, NULL);

// 		sigemptyset(&s_siquit.sa_mask);
// 		s_siquit.sa_flags = 0;
// 		s_siquit.sa_handler = SIG_IGN;
// 		sigaction(SIGQUIT, &s_siquit, NULL);

// 		// tcgetattr(STDIN_FILENO, &org_term);
// 		// new_term = org_term;
// 		// new_term.c_lflag &= ~(ECHO /* | ICANON */);
// 		// tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
// 		{
// 			while (true)
// 			{
// 				line = readline("minishell$ ");
// 				if (!line)
// 				{
// 					write(STDOUT_FILENO, "exit\n", 5);
// 					break ;
// 				}
// 				add_history(line);
// 				if (!ft_strcmp(line, "clh"))
// 					rl_clear_history();
// 				if (line[0] != '\n')
// 					printf("%s\n", line);
// 				free(line);
// 			}
// 		}
// 		// tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
// 	}
// 	else if (!isatty(STDIN_FILENO))
// 	{
// 		while (true)
// 		{
// 			line = readline(NULL);
// 			if (!line || !line[0])
// 				break ;
// 			free(line);
// 		}
// 	}
// 	(void)ac;
// 	(void)ev;
// 	(void)av;
// 	return (0);
// }
