/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:32:23 by rmei              #+#    #+#             */
/*   Updated: 2024/08/20 19:22:51 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"

# define REQUEST_COMPLETED SIGUSR1
# define REQUEST_PROCESSED SIGUSR2
# define SIGONE SIGUSR1
# define SIGZERO SIGUSR2

/* Prints the header for the minitalk server. */
void	ft_minitalk_header(void)
{
	ft_printf("\n+------------------------------------------------------+\n");
	ft_printf("|    _____   __        _____________       __   __     |\n");
	ft_printf("|   /     \\ |__| ____ |__\\__    ___/____  |  | |  | __ |\n");
	ft_printf(
		"|  /  \\ /  \\|  |/    \\|  | |    |  \\__  \\ |  | |  |/ / |\n");
	ft_printf("| /    Y    \\  |   |  \\  | |    |   / __ \\|  |_|    <  |\n");
	ft_printf("| \\____|__  /__|___|  /__| |____|  (____  /____/__|_ \\ |\n");
	ft_printf("|         \\/        \\/                  \\/          \\/ |\n");
	ft_printf("+------------------------------------------------------+\n\n");
}

/* Running. */
void	ft_server_status(void)
{
	ft_printf("[INFO] - Server active and listening...\n");
}

/* Raise an error and quit the program. */
void	ft_error(char *msg)
{
	char	*error;

	error = ft_strjoin("[ERROR] - ", msg);
	ft_putstr_fd(error, 2);
	free(error);
	exit(1);
}

#endif
