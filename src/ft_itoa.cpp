/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:12:07 by khatlas           #+#    #+#             */
/*   Updated: 2022/12/09 12:04:39 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	count_digits(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = (n / 10) * -1;
		i += 2;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static size_t	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

static int	fill_string(char *str, int n)
{
	int	i;

	i = 0;
	if (n / 10 != 0)
		i = fill_string(str, n / 10);
	else if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	str[i] = ft_abs(n % 10) + '0';
	i++;
	str[i] = '\0';
	return (i);
}

void	ft_itoa(int n, char *ptr)
{
	size_t	len;

	len = count_digits(n);
	if (len == 0)
		len = 1;
	fill_string(ptr, n);
}

int	ft_atoi(const char *str)
{
	long int	total;
	int			negate;

	total = 0;
	negate = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negate = negate * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total = total * 10 + (*str - 48);
		str++;
		if (total * negate > 2147483647)
			return (-1);
		if (total * negate < -2147483648)
			return (0);
	}
	return ((int) total * negate);
}