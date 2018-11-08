/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:55:23 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 14:49:45 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_md5_flags	g_md5_flags[5] =
{
	{ MD5_P, 'p' },
	{ MD5_Q, 'q' },
	{ MD5_R, 'r' },
	{ MD5_S, 's' },
	{ 0, 0 },
};

static int	search_flag(uint8_t *flags, char arg)
{
	int		idx;

	idx = 0;
	while (g_md5_flags[idx].flag)
	{
		if (arg == g_md5_flags[idx].c)
		{
			*flags |= g_md5_flags[idx].flag;
			return (0);
		}
		idx++;
	}
	return (1);
}

static int	usage(char *msg, char arg, int errnum)
{
	ft_putstr_fd("md5: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" -- ", 2);
	ft_putchar_fd(arg, 2);
	ft_putendl_fd("\nUsage: md5 [-pqrtx] [-s string] [files ...]", 2);
	return (errnum);
}

static int	manage_args(uint8_t *flags, char *arg)
{
	if (!(*flags & MD5_END) && *arg == '-')
	{
		while (*(++arg))
		{
			if (*flags & MD5_S)
				manage_string(flags, arg, arg, ft_strlen(arg));
			if (search_flag(flags, *arg))
				return (usage("illegal option", *arg, 1));
			if (*flags & MD5_P)
				manage_stdin(flags, 1);
		}
	}
	else if (*flags & MD5_S)
		manage_string(flags, arg, arg, ft_strlen(arg));
	else
		manage_file(flags, arg);
	return (0);
}

int			parse_args(int argc, char **argv)
{
	int		idx;
	uint8_t	flags;
	char	*arg;

	idx = 0;
	if (!argc)
		return (manage_stdin(&flags, 0));
	while (idx < argc)
	{
		arg = argv[idx];
		if (manage_args(&flags, arg))
			return (1);
		idx++;
	}
	if (flags & MD5_S)
		return (usage("option requires an argument", 's', 1));
	return (0);
}
