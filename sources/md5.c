/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:07:55 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/08 14:53:42 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static int	err_msg(char *msg, char *arg, int errnum)
{
	ft_putstr_fd("md5: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	return (errnum);
}

int			manage_string(uint8_t *flags, char *str, char *content, size_t len)
{
	*flags |= MD5_END;
	if (!((*flags & MD5_R) || (*flags & MD5_Q)))
	{
		ft_putstr("MD5 (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
	}
	ft_putstr(md5_digest(content, len));
	if ((*flags & MD5_R) && !(*flags & MD5_Q))
	{
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putstr("\"");
	}
	ft_putendl("");
	*flags ^= MD5_S;
	return (0);
}

int			manage_file(uint8_t *flags, char *filename)
{
	struct stat	st_stat;
	char		*content;
	int			fd;

	*flags |= MD5_END;
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
	*flags |= MD5_S;
	manage_string(flags, filename, content, st_stat.st_size);
	ft_strdel(&content);
	return (0);
}

int			manage_stdin(uint8_t *flags, uint8_t echo)
{
	size_t	size;
	char	*buff;

	size = ft_readfile(0, &buff);
	if (echo)
	{
		ft_putendl(buff);
		*flags ^= MD5_P;
	}
	ft_putendl(md5_digest(buff, size));
	ft_strdel(&buff);
	return (0);
}

int			md5(int argc, char **argv)
{
	parse_args(argc, argv);
	return (0);
}
