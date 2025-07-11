/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:35:54 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/08 09:36:02 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

void	sigquit_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	ft_putendl_fd("core dumped", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	g_exit_status = 131;
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	g_exit_status = 130;
}

void	signals_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	setup_heredoc_signals(bool ignore_sigint)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (ignore_sigint)
		sa.sa_handler = SIG_IGN;
	else
		sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	kill_process(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
