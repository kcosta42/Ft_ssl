/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:53:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/12 14:38:08 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_digest g_digest[3] =
{
	{ 3, "md5", &md5 },
	{ 6, "sha256", &sha256 },
	{ 0, NULL, NULL },
};

static int	usage(char *cmd)
{
	ft_putstr_fd("ft_ssl: Error: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("' is an invalid command.", 2);
	ft_putendl_fd("\nStandard commands:", 2);
	ft_putendl_fd("\nMessage Digest commands:", 2);
	ft_putendl_fd("md5", 2);
	ft_putendl_fd("sha256", 2);
	ft_putendl_fd("\nCipher commands:", 2);
	return (0);
}

static int	dispatcher(int argc, char **argv)
{
	int		i;
	char	*cmd;
	size_t	cmdlen;

	i = 0;
	cmd = argv[0];
	while (g_digest[i].cmd)
	{
		cmdlen = ft_strlen(cmd);
		if (cmdlen == g_digest[i].cmdlen && !ft_strcmp(cmd, g_digest[i].cmd))
			return (g_digest[i].exec(argc - 1, argv + 1));
		i++;
	}
	return (usage(cmd));
}

static int	ft_ssl(void)
{
	char	*input;

	ft_putstr("Ft_SSL> ");
	while (ft_getline(1, &input) > 0)
	{
		dispatcher(1, &input);
		ft_strdel(&input);
		ft_putstr("Ft_SSL> ");
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int		ret;

	if (argc < 2)
		return (ft_ssl());
	ret = dispatcher(argc - 1, argv + 1);
	return (ret);
}
