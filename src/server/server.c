/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:20:34 by rmei              #+#    #+#             */
/*   Updated: 2024/08/20 19:25:13 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Process and display the client request. */
void	ft_response_send(int sig, siginfo_t *info, void *context)
{
	static int				bit_count;
	static unsigned char	c;

	(void)context;
	c |= (sig == SIGONE);
	if (++bit_count == 8)
	{
		bit_count = 0;
		if (!c)
		{
			kill(info->si_pid, REQUEST_COMPLETED);
			ft_printf("\n");
			ft_server_status();
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		c <<= 1;
	kill(info->si_pid, REQUEST_PROCESSED);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc > 1)
		ft_error("The server must be started without passing any arguments.\n");
	ft_minitalk_header();
	ft_printf("[INFO] - Starting server `%s`...\n", argv[0]);
	ft_printf("[INFO] - PID: %i\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_response_send;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_server_status();
	while (1)
		pause();
	return (0);
}
