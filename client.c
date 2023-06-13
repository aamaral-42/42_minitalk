/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:06:22 by aamaral-          #+#    #+#             */
/*   Updated: 2023/04/20 20:07:23 by aamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	ft_atoi(const char *pid_ptr)
{
	int		index;
	pid_t	pid_decimal;

	index = 0;
	pid_decimal = 0;
	while (pid_ptr[index] >= '0' && pid_ptr[index] <= '9')
	{
		pid_decimal = 10 * pid_decimal + pid_ptr[index] - '0';
		index++;
	}
	return (pid_decimal);
}

int	invalid_arg(int argc, char **argv)
{
	size_t	index;

	if (argc != 3)
		return (write(1, "Enter three args:./client <pid> <message>\n", 42));
	if (*argv[2] == 0)
		return (write(1, "You've entered an empty message\n", 32));
	index = 0;
	while (argv[1][index])
	{
		if (!(argv[1][index] >= '0' && argv[1][index] <= '9'))
			return (write(1, "You didn't enter a number\n", 26));
		index++;
	}
	return (0);
}

int	transmmit_ascii_binary(char *message, pid_t server_process_id)
{
	int		index;
	int		base_two_exponent;
	char	symbol;

	index = 0;
	while (message[index])
	{
		base_two_exponent = 128;
		symbol = message[index];
		while (base_two_exponent > 0)
		{
			if (symbol >= base_two_exponent)
			{
				kill(server_process_id, SIGUSR1);
				symbol = symbol - base_two_exponent;
			}
			else
				kill(server_process_id, SIGUSR2);
			base_two_exponent = base_two_exponent / 2;
			usleep(242);
		}
		index++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	server_process_id;

	if (invalid_arg(argc, argv))
		return (-1);
	server_process_id = ft_atoi(argv[1]);
	transmmit_ascii_binary(argv[2], server_process_id);
	return (0);
}
