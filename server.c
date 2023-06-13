/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:07:50 by aamaral-          #+#    #+#             */
/*   Updated: 2023/04/20 20:07:55 by aamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

/*void	ft_putchar(char letter)
{
	write(1, &letter, 1);
}

void	ft_itoa(pid_t number_decimal)
{
	if (number_decimal < 10)
		ft_putchar(number_decimal + '0');
	else
	{
		ft_itoa(number_decimal / 10);
		ft_putchar(number_decimal % 10 + '0');
	}
}*/

void	ft_itoa(pid_t number)
{
	if (number >= 9)
		ft_itoa(number / 10);
	write(1, &"0123456789"[number % 10], 1);
}

void	convert_bits_to_char(char *binary_str)
{
	char	bit;
	int		base_two_exponent;
	int		index;
	int		ascii_value;

	index = 0;
	while (binary_str[index])
	{
		base_two_exponent = 128;
		ascii_value = 0;
		while (base_two_exponent >= 1)
		{	
			bit = binary_str[index];
			if (bit == '1')
				ascii_value += base_two_exponent;
			base_two_exponent /= 2;
			index++;
		}
		write(1, &ascii_value, 1);
	}
}

void	save_str_bit(int sig)
{
	static char	binary_str[8];
	static int	bit_counter = 0;

	if (sig == SIGUSR1)
		binary_str[bit_counter] = '1';
	else if (sig == SIGUSR2)
		binary_str[bit_counter] = '0';
	bit_counter++;
	if (bit_counter == 8)
	{
		bit_counter = 0;
		convert_bits_to_char(binary_str);
	}
}

int	main(void)
{
	ft_itoa(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, save_str_bit);
	signal(SIGUSR2, save_str_bit);
	while (1)
		pause();
	return (0);
}
