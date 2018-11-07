/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:53:15 by kcosta            #+#    #+#             */
/*   Updated: 2018/11/07 17:56:32 by kcosta           ###   ########.fr       */
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
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(cmd);
	ft_putendl("' is an invalid command.");
	ft_putendl("\nStandard commands:");
	ft_putendl("\nMessage Digest commands:");
	ft_putendl("md5");
	ft_putendl("sha256");
	ft_putendl("\nCipher commands:");
	return (0);
}

int			dispatcher(int argc, char **argv)
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

int			main(int argc, char **argv)
{
	int		ret;

	if (argc < 2)
		return (-1); // ADD Command line
	ret = dispatcher(argc - 1, argv + 1);
	return (ret);
}
