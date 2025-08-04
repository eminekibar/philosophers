/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:39 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 20:05:39 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

char	*is_valid(char *str, t_table *table)
{
	int		len;
	char	*number;

	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		exit_safe("Only positive numbers!", EXIT_FAILURE, table);
	number = str;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		len++;
		str++;
	}
	if (!(*str >= '0' && *str <= '9') && *str != '\0')
		exit_safe("Only positive numbers!", EXIT_FAILURE, table);
	if (len > 10)
		exit_safe("Integer limit error!", EXIT_FAILURE, table);
	return (number);
}

long	ft_atol(char *str, t_table *table)
{
	int		i;
	long	num;

	num = 0;
	str = is_valid(str, table);
	i = -1;
	while (str[++i] >= '0' && str[i] <= '9')
		num = num * 10 + str[i] - '0';
	if (num > INT_MAX)
		exit_safe("Integer limit error!", EXIT_FAILURE, table);
	return (num);
}
