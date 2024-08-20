/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:20:26 by rmei              #+#    #+#             */
/*   Updated: 2024/08/20 18:46:58 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_request_processed = 0;

void	ft_request_status(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_request_processed = 1;
	if (sig == REQUEST_COMPLETED)
		ft_printf(
			"[%i] - Server %i processed the request.\n", sig, info->si_pid);
}

void	ft_request_send(int pid, char *request)
{
	int				bit_shift;
	unsigned char	c;

	while (1)
	{
		c = *request;
		bit_shift = 8;
		while (bit_shift--)
		{
			if ((c >> bit_shift) & 1)
				kill(pid, SIGONE);
			else
				kill(pid, SIGZERO);
			while (!g_request_processed)
				pause();
			g_request_processed = 0;
		}
		if (!*request)
			break ;
		request++;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	char				*request;
	struct sigaction	sa;

	if (argc != 3)
		ft_error("The client requires a server PID and a request message.\n");
	server_pid = ft_atoi(argv[1]);
	request = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_request_status;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_request_send(server_pid, request);
	return (0);
}
