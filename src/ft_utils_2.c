/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:59:53 by lconiau           #+#    #+#             */
/*   Updated: 2024/04/19 13:02:50 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	countnum(int n)
{
	size_t			i;
	unsigned int	nb;

	i = 0;
	if (n < 0)
	{
		nb = -n;
		i++;
	}
	else
		nb = n;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}

static void	ft_putnbr(long int nb, char *str, size_t *i)
{
	unsigned long int	absolut;

	if (nb < 0)
	{
		absolut = -nb;
		str[*i] = '-';
		*i += 1;
	}
	else
		absolut = nb;
	if (absolut > 9)
	{
		ft_putnbr(absolut / 10, str, i);
	}
	str[*i] = absolut % 10 + '0';
	*i += 1;
}

char	*ft_itoa(long int n)
{
	int		count;
	char	*str;
	size_t	i;

	i = 0;
	count = countnum(n);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_putnbr(n, str, &i);
	str[count] = '\0';
	return (str);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] > 7 && str[i] < 15))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	err_msg(char *err_msg)
{
	perror(err_msg);
	exit(1);
}
