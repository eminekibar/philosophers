/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:48:35 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 21:31:05 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strjoin_args(int argc, char **argv)
{
	int		i;
	int		len;
	char	*joined;
	int		j;

	len = 0;
	i = 1;
	while (i < argc)
		len += ft_strlen(argv[i++]) + 1;
	joined = (char *)malloc(sizeof(char) * len);
	if (!joined)
		return (NULL);
	len = 0;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
			joined[len++] = argv[i][j++];
		if (i < argc - 1)
			joined[len++] = ' ';
		i++;
	}
	joined[len] = '\0';
	return (joined);
}

char	**argv_split(int *argc, char **argv)
{
	char	*joined_args;

	joined_args = ft_strjoin_args(*argc, argv);
	if (!joined_args)
		return (NULL);
	argv = ft_split(joined_args, ' ');
	free(joined_args);
	*argc = 0;
	while (argv[*argc])
		*argc += 1;
	return (argv);
}
