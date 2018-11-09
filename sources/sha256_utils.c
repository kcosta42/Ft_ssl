/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:05:39 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:14:50 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

t_sha256_flags	g_sha256_flags[5] =
{
	{ SHA256_P, 'p' },
	{ SHA256_Q, 'q' },
	{ SHA256_R, 'r' },
	{ SHA256_S, 's' },
	{ 0, 0 },
};

static int	search_flag(uint8_t *flags, char arg)
{
	int		idx;

	idx = 0;
	while (g_sha256_flags[idx].flag)
	{
		if (arg == g_sha256_flags[idx].c)
		{
			*flags |= g_sha256_flags[idx].flag;
			return (0);
		}
		idx++;
	}
	return (1);
}

static int	usage(char *msg, char arg, int errnum)
{
	ft_putstr_fd("sha256: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" -- ", 2);
	ft_putchar_fd(arg, 2);
	ft_putendl_fd("\nUsage: sha256 [-pqrtx] [-s string] [files ...]", 2);
	return (errnum);
}

static int	manage_args(uint8_t *flags, char *arg)
{
	if (!(*flags & SHA256_END) && *arg == '-')
	{
		while (*(++arg))
		{
			if (*flags & SHA256_S)
			{
				sha256_manage_string(flags, arg, arg, ft_strlen(arg));
				break ;
			}
			if (search_flag(flags, *arg))
				return (usage("illegal option", *arg, 1));
			if (*flags & SHA256_P)
				sha256_manage_stdin(flags, 1);
		}
	}
	else if (*flags & SHA256_S)
		sha256_manage_string(flags, arg, arg, ft_strlen(arg));
	else
		sha256_manage_file(flags, arg);
	return (0);
}

int			sha256_parse_args(int argc, char **argv)
{
	int		idx;
	uint8_t	flags;
	char	*arg;

	idx = 0;
	if (!argc)
		return (sha256_manage_stdin(&flags, 0));
	while (idx < argc)
	{
		arg = argv[idx];
		if (manage_args(&flags, arg))
			return (1);
		idx++;
	}
	if (flags & SHA256_S)
		return (usage("option requires an argument", 's', 1));
	if (!(flags & SHA256_INPUT))
		return (sha256_manage_stdin(&flags, 0));
	return (0);
}
