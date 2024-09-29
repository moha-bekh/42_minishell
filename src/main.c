/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/09/29 19:07:33 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_stdio_init(void)
{
	int	fd;

	fd = open("/dev/stdin", O_RDWR);
	if (fd == -1)
		return (_FAILURE);
	fd = open("/dev/stdout", O_RDWR);
	if (fd == -1)
		return (_FAILURE);
	fd = open("/dev/stderr", O_RDWR);
	if (fd == -1)
		return (_FAILURE);
	fd = 2;
	while (++fd < 6)
		close(fd);
	return (_SUCCESS);
}

int	_shell_init(t_pdata data)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &data->shell.org_term) == -1)
			return (_FAILURE);
		data->shell.new_term = data->shell.org_term;
		data->shell.new_term.c_lflag |= (ICANON | ECHO | ECHOE | ECHOK | ISIG | IEXTEN); // Active les flags utilisés par bash
		data->shell.new_term.c_lflag &= ~(ECHONL | ECHOPRT | ECHOKE); // Désactive d'autres options inutiles pour bash
		if (tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term) == -1)
			return (_FAILURE);
	}
	return (_SUCCESS);
}

void	_hndl_sigint(int sig)
{
	(void)sig;
	*g_ptr_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	_sig_init_sas(t_pdata data)
{
	sigemptyset(&data->shell.s_sigint.sa_mask);
	data->shell.s_sigint.sa_flags = 0;
	data->shell.s_sigint.sa_handler = _hndl_sigint;
	sigaction(SIGINT, &data->shell.s_sigint, NULL);

	sigemptyset(&data->shell.s_sigquit.sa_mask);
	data->shell.s_sigquit.sa_flags = 0;
	data->shell.s_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	if (_stdio_init() || _shell_init(&data) || _sig_init_sas(&data))
		return (_FAILURE);
	if (_data_init(&data, ac, av, ev))
		return (_data_clear(&data), _FAILURE);
	while (true)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			return (write(1, "exit\n", 5), _data_clear(&data));
		add_history(data.prompt);
		if (_tok_list(&data) && !_data_structs_clear(&data))
			continue ;
		// _dlst_print_tokens(data.tokens);
		_tree_builder(&data.tree, data.tokens->d_top);
		if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
			continue ;
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}

// void _hndl_int(int sig)
// {
// 	printf("SIGINT: %d\n", sig);
// }

// int	main(int ac, char **av, char **ev)
// {
// 	char *line;
// 	pid_t pid;
// 	int status;
// 	struct sigaction	_sig_int;
// 	struct sigaction	_sig_quit;

// 	sigemptyset(&_sig_int.sa_mask);
// 	_sig_int.sa_flags = 0;
// 	_sig_int.sa_handler = _hndl_int;
// 	sigaction(SIGINT, &_sig_int, NULL);

// 	sigemptyset(&_sig_quit.sa_mask);
// 	_sig_quit.sa_flags = 0;
// 	_sig_quit.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &_sig_quit, NULL);

// 	while (true)
// 	{
// 		line = readline("main$ ");
// 		if (!line)
// 			return (write(1, "exit\n", 5), _SUCCESS);

// 		if (!ft_strcmp(line, "hd"))
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				_sig_int.sa_handler = SIG_DFL;
// 				_sig_quit.sa_handler = SIG_DFL;
// 				sigaction(SIGINT, &_sig_int, NULL);
// 				sigaction(SIGQUIT, &_sig_quit, NULL);
// 				printf("child\n");
// 				sleep(5);
// 				exit(0);
// 			}
// 			else
// 			{
// 				_sig_int.sa_handler = SIG_IGN;
// 				_sig_quit.sa_handler = SIG_IGN;
// 				sigaction(SIGINT, &_sig_int, NULL);
// 				sigaction(SIGQUIT, &_sig_quit, NULL);

// 				waitpid(pid, &status, 0);
// 				if(WIFEXITED(status))
// 					printf("exit status: %d\n", WEXITSTATUS(status));
// 				else if (WIFSIGNALED(status))
// 					printf("sig status: %d\n", WTERMSIG(status) + 128);
// 				printf("status: %d\n", status);
// 			}
// 		}
// 		printf("line: %s\n", line);
// 	}
// 	(void)ac;
// 	(void)av;
// 	(void)ev;
// 	return (_SUCCESS);
// }
