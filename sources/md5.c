/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:07:55 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/07 19:11:05 by kcosta           ###   ########.fr       */
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

static int	usage(void)
{
	ft_putendl("md5: option requires an argument -- s");
	ft_putendl("Usage: md5 [-pqrtx] [-s string] [files ...]");
	return (0);
}

static int	search_flag(uint8_t *flag, char arg)
{
	int		idx;

	idx = 0;
	while (g_md5_flags[idx].flag)
	{
		if (arg == g_md5_flags[idx].c)
		{
			*flag |= g_md5_flags[idx].flag;
			return (0);
		}
		idx++;
	}
	return (0);
}

static int	err_msg(char *msg, char *arg, int errnum)
{
	ft_putstr_fd("md5: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	return (errnum);
}

static int	manage_string(uint8_t *flag, char *str, char *content)
{
	if (!((*flag & MD5_R) || (*flag & MD5_Q)))
	{
		ft_putstr("MD5 (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
	}
	(void)content;
	ft_putstr("4f88641846f1453f4636ff");
	if ((*flag & MD5_R) && !(*flag & MD5_Q))
	{
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putstr("\"");
	}
	ft_putendl("");
	*flag ^= MD5_S;
	return (0);
}

static int	manage_file(uint8_t *flag, char *filename)
{
	struct stat	st_stat;
	char		*content;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1 && errno == EACCES)
		return (err_msg(": Permission denied", filename, -1));
	else if (fd == -1)
		return (err_msg(": No such file or directory", filename, -2));
	else if (fstat(fd, &st_stat) == -1)
		return (err_msg(": Permission denied", filename, -1));
	else if (S_ISDIR(st_stat.st_mode))
		return (err_msg(": Is a directory", filename, -3));
	content = ft_strnew(st_stat.st_size);
	read(fd, content, st_stat.st_size);
	close(fd);
	*flag |= MD5_S;
	manage_string(flag, filename, content);
	ft_strdel(&content);
	return (0);
}

static int	parse_args(int argc, char **argv)
{
	int		idx;
	uint8_t	flag;
	char	*arg;

	idx = 0;
	while (idx < argc)
	{
		arg = argv[idx];
		if (!(flag & MD5_END) && *arg == '-')
		{
			while (*(++arg))
			{
				if (flag & MD5_S)
					manage_string(&flag, arg, arg);
				if (search_flag(&flag, *arg))
					return (usage());
			}
			flag |= MD5_END;
		}
		else if (flag & MD5_S)
			manage_string(&flag, arg, arg);
		else
			manage_file(&flag, arg);
		idx++;
	}
	return (0);
}

int			md5(int argc, char **argv)
{
	parse_args(argc, argv);
	return (0);
}
