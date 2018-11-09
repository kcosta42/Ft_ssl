/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:07:58 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/09 14:15:26 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static int	err_msg(char *msg, char *arg, int errnum)
{
	ft_putstr_fd("sha526: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	return (errnum);
}

int			sha256_manage_string(uint8_t *flags, char *str, char *c, size_t l)
{
	*flags |= SHA256_INPUT;
	if (!((*flags & SHA256_R) || (*flags & SHA256_Q)))
	{
		ft_putstr("SHA256 (");
		*flags & SHA256_END ? 0 : ft_putstr("\"");
		ft_putstr(str);
		*flags & SHA256_END ? 0 : ft_putstr("\"");
		ft_putstr(") = ");
	}
	ft_putstr(sha256_digest(c, l));
	if ((*flags & SHA256_R) && !(*flags & SHA256_Q))
	{
		*flags & SHA256_END ? ft_putstr(" ") : ft_putstr(" \"");
		ft_putstr(str);
		*flags & SHA256_END ? 0 : ft_putstr("\"");
	}
	ft_putendl("");
	*flags ^= SHA256_S;
	return (0);
}

int			sha256_manage_file(uint8_t *flags, char *filename)
{
	struct stat	st_stat;
	char		*content;
	int			fd;

	*flags |= SHA256_END;
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
	*flags |= SHA256_S;
	sha256_manage_string(flags, filename, content, st_stat.st_size);
	ft_strdel(&content);
	return (0);
}

int			sha256_manage_stdin(uint8_t *flags, uint8_t echo)
{
	size_t	size;
	char	*buff;
	char	tmp;

	*flags |= SHA256_INPUT;
	size = ft_readfile(0, &buff);
	if (echo)
	{
		tmp = buff[size - 1];
		buff[size - 1] = 0;
		ft_putendl(buff);
		*flags ^= SHA256_P;
		buff[size - 1] = tmp;
	}
	ft_putendl(sha256_digest(buff, size));
	ft_strdel(&buff);
	return (0);
}

int			sha256(int argc, char **argv)
{
	sha256_parse_args(argc, argv);
	return (0);
}
